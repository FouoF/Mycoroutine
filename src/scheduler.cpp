#include"scheduler.h"

namespace mycoroutine{

static thread_local std::shared_ptr<Scheduler> t_scheduler = nullptr;
//the main fiber executing the scheduler
static thread_local std::shared_ptr<Fiber> t_fiber = nullptr;

Scheduler::Scheduler(size_t thread_num = 1, bool use_caller = true, std::string name = "DEFAULT") : m_name(name){
    if (use_caller){
        m_mainfiber = mycoroutine::Fiber::GetThis();
        thread_num--;
        t_fiber = m_mainfiber;
        t_scheduler = shared_from_this();
        m_rootThread = mycoroutine::GetThreadId();
        m_mainfiber->reset(std::bind(&Scheduler::run, this));
    }
    else {
        m_rootThread = -1;
    }
    m_threadCount = thread_num;
}; 
virtual Scheduler::~Scheduler(){
    if (t_scheduler.get() = this) 
    t_scheduler = nullptr;
};

std::shared_ptr<Scheduler> Scheduler::GetThis(){
    return t_scheduler;
};
std::shared_ptr<Fiber> Scheduler::GetMainFiber(){
    return m_mainfiber;
};

void Scheduler::start(){
    MutexLock lock(m_mutex);
    if (!m_stopping)
    return;
    m_stopping = false;
    m_threads.resize(m_threadCount);
    for (size_t i = 0; i < m_threadCount; i++){
        m_threads[i].reset(new Thread(std::bind(&Scheduler::run, this),
         m_name + "_" + std::to_string(i)));
        m_threadIds.push_back(m_threads[i]->getId());
    }
};

//elegant stop
void Scheduler::stop(){
    m_autoStop = true;
    //the scheduler is ready to stop
    if (m_mainfiber && m_threadCount = 0 
    && (m_mainfiber->getState() == Fiber::TERM || m_mainfiber->getState() == Fiber::INIT)){
        m_stopping = true;
        if (stopping()){
            return; 
    }
    }
    bool exit_on_this_fiber = false;
    m_stopping = true;
    for (size_t i = 0; i < m_threadCount; i ++){
        tickle();
    }
    if (m_mainfiber){
        tickle();
    }
    if (stopping())
        return;
};

void Scheduler::run(){
    t_scheduler = shared_from_this();
    if (mycoroutine::GetThreadId() != m_rootThread){
        t_fiber = Fiber::GetThis();
    }
    FiberAndThread ft;
    std::shared_ptr<Fiber> idel_fiber = Fiber::Create(std::bind(&Scheduler::idel, this), 4096);
    //TODO:define default stacksize
    std::shared_ptr<Fiber> cb_fiber = Fiber::Create(nullptr, 4096);
    while(true){
        bool need_tickle = false;
        ft.reset();
        {   
            MutexLock lock(m_mutex);
            auto it = m_fibers.begin();
            while(it != m_fibers.end()){
                if (it->thread != -1 && it->thread != GetThreadId()){
                    ++it;
                    need_tickle = true;
                    continue;
                }
                if (it->fiber && it->fiber->getState == Fiber::EXEC){
                    ++it;
                    continue;
                }
                ft = *it;
                m_fibers.erase(it);
            }
        }
        if (need_tickle) tickle();
        if (ft.fiber && ft.fiber->getState() != Fiber::TERM){
            ++m_activeThreadCount;
            ft.fiber->swapIn();
            --m_activeThreadCount;
            //consider the state after swapout [READY, HOLD, TERM]
            if (ft.fiber->getState() == Fiber::READY) schedule(ft.fiber);
            else ft.fiber->m_state = Fiber::HOLD;
            ft.reset();
        }
        //the param is a function
        else if (ft.cb){
            cb_fiber->reset(ft.cb);
            ft.reset();
            ++m_activeThreadCount;
            cb_fiber->swapIn();
            --m_activeThreadCount;
            if (cb_fiber->getState() == Fiber::READY){
                std::shared_ptr<Fiber> shared_fiber(cb_fiber);
                schedule(shared_fiber);
            }
            else if (cb_fiber->getState() == Fiber::TERM){
                cb_fiber->m_state = Fiber::HOLD;
            }
            cb_fiber->reset(nullptr);
        }
        else{
            ++m_idelThreadCount;
            idel_fiber->swapIn();
            if (idel_fiber->getState() == Fiber::TERM){
                idel_fiber = nullptr;
            }
            --m_idelThreadCount;
        }
}
}