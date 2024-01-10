#if !defined(_MYCOROUTINE_IOMANAGER_H_)
#define _MYCOROUTINE_IOMANAGER_H_
#include"scheduler.h"

namespace mycoroutine{
class IOManager : public Scheduler{
public:
    enum Event{
        NONE  = 0x0,
        READ  = 0x1,
        WRITE = 0x2,
    };
private:
    struct FdContext{
        RWMutex mutex;
        struct EventContext{
            std::shared_ptr<Scheduler> scheduler = nullptr;
            std::shared_ptr<Fiber> fiber = nullptr;
            std::function<void()> cb;
        };
        void trigger(EventContext ctx){
            if (ctx.cb){
                ctx.scheduler->schedule(&ctx.cb);
            }
            else {
                ctx.scheduler->schedule(&ctx.fiber);
            }
        }
        void reset(EventContext ctx){
            ctx.scheduler.reset();
            ctx.fiber.reset();
            ctx.cb = NULL;
        };
        EventContext& getContext(Event event){
            if (event == READ) return readEvent;
            return writeEvent;
        };
        void resetContext(Event event){
            if (event == READ) 
                reset(readEvent);
            else if 
                (event == WRITE)
                 reset(writeEvent);
            else {
                reset(readEvent);
                reset(writeEvent);
            }
        }
        void triggerEvent(Event event){
            if (event == READ){
                trigger(readEvent);
                reset(readEvent);
            }
            else if (event == WRITE){
                trigger(readEvent);
                reset(readEvent);
            }
            else {
                trigger(readEvent);
                reset(readEvent);
                trigger(writeEvent);
                reset(writeEvent);
            }
        }
        EventContext readEvent;
        EventContext writeEvent;
        int fd = 0;
        Event m_events = NONE;
    };
public:
    IOManager(size_t thread_num = 1, bool use_caller = true, std::string name = "DEFAULT"); 
    ~IOManager() override;

    //0:success, -1:error
    int addEvent(int fd, Event event, std::function<void()> cb);
    bool deleteEvent(int fd, Event event);
    bool cancelEvent(int fd, Event event);
    bool cancelAll(int fd);

    static std::shared_ptr<IOManager> GetThis();
protected:
    void tickle() override;
    bool stopping() override;
    void idel() override;
    void contextsResize(int size);
private:
    int m_epfd = 0;
    int m_tickleFds[2];
 
    std::atomic<size_t> m_pendingEventCount = {0};
    RWMutex m_mutex;
    std::vector<FdContext*> m_fdContexts;  
};
}

#endif // _MYCOROUTINE_IOMANAGER_H_