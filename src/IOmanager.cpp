#include"IOmanager.h"

#include<sys/epoll.h>
#include<unistd.h>
#include<fcntl.h>

namespace mycoroutine{

    IOManager::IOManager(size_t thread_num, bool use_caller, std::string name)
    : Scheduler(thread_num, use_caller, name){
        m_epfd = epoll_create(5000);
        pipe(m_tickleFds);

        epoll_event event;
        event.events = EPOLLIN | EPOLLET;
        event.data.fd = m_tickleFds[0];
        fcntl(m_tickleFds[0], F_SETFL, O_NONBLOCK);
        epoll_ctl(m_epfd, EPOLL_CTL_ADD, m_tickleFds[0], &event);
        contextsResize(32);

        start();
    } 
    IOManager::~IOManager(){
        stop();
        close(m_epfd);
        close(m_tickleFds[0]);
        close(m_tickleFds[1]);

        for (int i = 0; i < m_fdContexts.size(); i++){
            if (m_fdContexts[i]){
                delete m_fdContexts[i];
                m_fdContexts[i] = nullptr;
            }
        }
    }

    void IOManager::contextsResize(size_t size){
        m_fdContexts.resize(size);
        for (int i = 0; i < size; ++ i){
            if (!m_fdContexts[i]){
                m_fdContexts[i] = new FdContext();
                m_fdContexts[i]->fd = i;
            }
        }
    }
    int IOManager::addEvent(int fd, Event event, std::function<void()> cb){
        FdContext * fd_ctx = nullptr;
        ReadLock lock(m_mutex);
        if (m_fdContexts.size() > fd){
            fd_ctx = m_fdContexts[fd];
            lock.unlock();
        }
        else {
            lock.unlock();
            WrLock lock(m_mutex);
            contextsResize(m_fdContexts.size() * 2);

            if (m_fdContexts.size() <= fd){
                std::cerr << "addEvent:bad fd" << std::endl;
                return -1;
            }

            fd_ctx = m_fdContexts[fd];
            lock.unlock();
        }

        WrLock lock2(fd_ctx->mutex);
        int op = fd_ctx->m_events ? EPOLL_CTL_MOD : EPOLL_CTL_ADD;
        epoll_event epevent;
        epevent.events = EPOLLET | fd_ctx->m_events | event;
        epevent.data.ptr = fd_ctx;
        epoll_ctl(m_epfd, op, fd, &epevent);

        ++ m_pendingEventCount;

        fd_ctx->m_events = (Event)(fd_ctx->m_events | event);
        FdContext::EventContext& event_ctx = fd_ctx->getContext(event);
        event_ctx.scheduler = Scheduler::GetThis();
        if (cb){
            event_ctx.cb.swap(cb);
        }
        return 0;
    };

    bool IOManager::deleteEvent(int fd, Event event){
        ReadLock lock(m_mutex);
        if (fd >= m_fdContexts.size()) return false;
        FdContext* fd_ctx = m_fdContexts[fd];
        lock.unlock();
        WrLock lock2(m_mutex);
        if (fd_ctx->m_events & event != 0){
            return false;
        }
        Event new_event = (Event)(fd_ctx->m_events & ~event);
        int op = new_event ? EPOLL_CTL_MOD : EPOLL_CTL_DEL;
        epoll_event ev;
        ev.events = EPOLLET | new_event;
        ev.data.ptr = fd_ctx;
        epoll_ctl(m_epfd, op, fd, &ev);
        --m_pendingEventCount;
        fd_ctx->m_events = new_event;
        fd_ctx->resetContext(event);
        return true;
    };

    bool IOManager::cancelEvent(int fd, Event event){
        ReadLock lock(m_mutex);
        if (fd >= m_fdContexts.size()) return false;
        FdContext* fd_ctx = m_fdContexts[fd];
        lock.unlock();
        WrLock lock2(m_mutex);
        if (fd_ctx->m_events & event != 0){
            return false;
        }
        Event new_event = (Event)(fd_ctx->m_events & ~event);
        int op = new_event ? EPOLL_CTL_MOD : EPOLL_CTL_DEL;
        epoll_event ev;
        ev.events = EPOLLET | new_event;
        ev.data.ptr = fd_ctx;
        epoll_ctl(m_epfd, op, fd, &ev);
        --m_pendingEventCount;        
        fd_ctx->triggerEvent(event);
        return true;
    };

    bool IOManager::cancelAll(int fd){
        ReadLock lock(m_mutex);
        if (fd >= m_fdContexts.size()) return false;
        FdContext* fd_ctx = m_fdContexts[fd];
        lock.unlock();
        WrLock lock2(m_mutex);
        Event event = fd_ctx->m_events;
        epoll_event ev;
        epoll_ctl(m_epfd, EPOLL_CTL_DEL, fd, &ev);
        fd_ctx->triggerEvent(event);
        --m_pendingEventCount;
        return true;
    };

    std::shared_ptr<IOManager> IOManager::GetThis(){
        return std::dynamic_pointer_cast<IOManager>(Scheduler::GetThis());
    };

    void IOManager::tickle(){
        if (!m_idelThreadCount){
            return;
        }
        write(m_tickleFds[1], "T", 1);
    };

    bool IOManager::stopping(){
        return  Scheduler::stopping() && m_pendingEventCount == 0;
    };

    void IOManager::idel(){
        epoll_event *events = new epoll_event[64]();
        std::shared_ptr<epoll_event> shared_events(events, [events](epoll_event * ptr){
            delete[] events;
        });
        
        while(true){
            if (stopping()) break;
            int rt = 0;
            while(rt <= 0){
                static const int MAX_TIMEOUT = 5000;
                rt = epoll_wait(m_epfd, events, 64, MAX_TIMEOUT);
            }
            for (int i = 0; i < rt; ++ i){
                epoll_event& event = events[i];
                if (event.data.fd == m_tickleFds[0]){
                    uint8_t tmp;
                    while(read(m_tickleFds[0], &tmp, 1) == 1);
                    continue;
                }

                FdContext *fd_ctx = (FdContext *)event.data.ptr;
                WrLock lock(fd_ctx->mutex);
                if (fd_ctx->m_events & (EPOLLHUP | EPOLLERR)){
                    event.events |= EPOLLIN | EPOLLOUT;
                }
                int real_events = NONE;
                if (event.events & EPOLLIN) {
                    real_events |= READ;
                }
                if (event.events & EPOLLOUT) {
                    real_events |= WRITE;
                }
                if ((fd_ctx->m_events & real_events) == NONE){
                    continue;
                }

                int left_events = (fd_ctx->m_events & ~real_events);
                int op = left_events ? EPOLL_CTL_MOD : EPOLL_CTL_DEL;
                event.events = EPOLLET | left_events;
                epoll_ctl(m_epfd, op, fd_ctx->fd, &event);
                fd_ctx->triggerEvent((Event)real_events);

                auto cur = Fiber::GetThis();
                Fiber * fiber_ptr = cur.get();
                cur.reset();

                fiber_ptr->swapOut();
            }
        }
    };
}