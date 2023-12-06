#ifndef _MYCOROUTINE_SCHEDULER_H_
#define _MYCOROUTINE_SCHEDULER_H_

#include<memory>
#include<vector>
#include<list>

#include"thread.h"
#include"fiber.h"

namespace mycoroutine{

class Scheduler : std::enable_shared_from_this<Scheduler>{
public:
    Scheduler(size_t thread_num = 1, bool use_caller = true, std::string name = "DEFAULT"); 
    virtual ~Scheduler();

    static std::shared_ptr<Scheduler> GetThis();
    static std::shared_ptr<Fiber> GetMainFiber();

    const std::string getName() const{
        return m_name;
    }

    void start();
    void stop();

    template<class FiberOrCb> 
    void schedule(FiberOrCb fc, int thread = -1){
        bool need_tickle = false;
        MutexLock lock(m_mutex);
        need_tickle = scheduleNolock(fc, thread);
        if (need_tickle) tickle();
    };

    template<class InputItrator>
    void schedule(InputItrator begin, InputItrator end){
        bool need_tickle = false;
        MutexLock lock(m_mutex);
        while(begin != end){
            need_tickle = scheduleNolock(*begin) || need_tickle;
            begin ++;
        }
        if (need_tickle) tickle();
    }
protected:
    virtual void tickle();
    void run();
    virtual bool stopping();
    virtual void idel();
private:
    template<class FiberOrCb>
    bool scheduleNolock(FiberOrCb fc, int thread){
        bool need_tickle = m_fibers.empty();
        FiberAndThread ft(fc, thread);
        if (ft.cb || ft.fiber){
            m_fibers.push_back(ft);            
        }
        return need_tickle;
    };
private:
    struct FiberAndThread{
        std::shared_ptr<Fiber> fiber;
        std::function<void()> cb;
        int thread;
        FiberAndThread(std::function<void()> f, int thr) : cb(f), thread(thr){};
        FiberAndThread(std::shared_ptr<Fiber> f, int thr) : fiber(f), thread(thr){};
        FiberAndThread():thread(-1){};
        void reset(){
            fiber = nullptr;
            cb = nullptr;
            thread = -1;
        }
    };
private:
    myMutex m_mutex = myMutex();
    std::shared_ptr<Fiber> m_mainfiber;
    std::string m_name;
    std::vector<std::shared_ptr<Thread> > m_threads;
    std::list<FiberAndThread> m_fibers;
protected:
    //mappping thread_id and index
    std::vector<pid_t> m_threadIds;
    size_t m_threadCount = 0;
    size_t m_activeThreadCount = 0;
    size_t m_idelThreadCount = 0;
    bool m_stopping = true;
    bool m_autoStop = false;
    pid_t m_rootThread = 0;
};
}

#endif