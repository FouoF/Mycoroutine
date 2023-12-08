#include"fiber.h"

namespace mycoroutine{

static std::atomic_int64_t s_fiber_id(0);
//point to the main fiber
static thread_local std::shared_ptr<Fiber> t_mainfiber = nullptr;
//point to current fiber
static thread_local std::shared_ptr<Fiber> t_fiber = nullptr;

class StackAllocator{
public: 
    static void * Alloc(size_t size){
        return malloc(size);
    }
    static void Dealloc(void * vp){
        free(vp);
    }
};
    //only one main fiber can exist
    std::shared_ptr<Fiber> Fiber::MainInit(){
        if (t_mainfiber) return t_mainfiber;
        std::shared_ptr<Fiber> ret = std::make_shared<Fiber>();
        t_mainfiber = ret;
        return ret;
    }

    std::shared_ptr<Fiber> Fiber::Create(std::function<void()> cb, size_t stacksize){
        return std::make_shared<Fiber>(cb, stacksize);
    }

    Fiber::Fiber(){
        m_state = INIT;
    }

    Fiber::Fiber(std::function<void()> cb, size_t stacksize)
     : m_cb(cb),
     m_id(++s_fiber_id), 
     m_stacksize(stacksize)
     {
        m_state = INIT;
        m_stack = StackAllocator::Alloc(m_stacksize);
        getcontext(&m_ctx);
        m_ctx.uc_link = &t_mainfiber->m_ctx;
        m_ctx.uc_stack.ss_sp = m_stack;
        m_ctx.uc_stack.ss_size = m_stacksize;
        makecontext(&m_ctx, &Fiber::MainFunc, 0);
        m_state = READY;
     };

    Fiber::~Fiber(){
        //destruct child Fiber
        if (m_stack){
            if (m_state == INIT || m_state == TERM){
                StackAllocator::Dealloc(m_stack);
            }
            else {
                std::cerr << "Fiber " << m_id << " destruct at wrong state!" << std::endl;
                StackAllocator::Dealloc(m_stack);
            }
        }
        //destruct main Fiber in case outside distruct
        else {
            t_fiber = nullptr;
        }
    }

    void Fiber::reset(std::function<void()> cb){
        if ((m_state == TERM || m_state == INIT) && m_stack){
            m_cb = cb;
            getcontext(&m_ctx);
            m_ctx.uc_link = &t_mainfiber->m_ctx;
            m_ctx.uc_stack.ss_sp = m_stack;
            m_ctx.uc_stack.ss_size = m_stacksize;
            makecontext(&m_ctx, &Fiber::MainFunc, 0);
            m_state = INIT;
        }
        else if ((m_state == INIT)){
            m_cb = cb;
            getcontext(&m_ctx);
            m_ctx.uc_link = &t_mainfiber->m_ctx;
        }
    };

    void Fiber::swapIn(){
        if (m_state != EXEC){
            SetThis(getShared());
            m_state = EXEC;
            swapcontext(&t_mainfiber->m_ctx, &m_ctx);
        }
        else std::cerr << "Fiber " << m_id << " swap at wrong state!" << std::endl;
    };

    void Fiber::swapOut(){
        SetThis(t_mainfiber);
        swapcontext(&m_ctx, &t_mainfiber->m_ctx);
    };

    void Fiber::SetThis(std::shared_ptr<Fiber> p){
        t_fiber = p;
    };

    //if the thread has no main fiber, GetThis() will create one automatically
    std::shared_ptr<Fiber> Fiber::GetThis(){
        if (t_fiber)
        return t_fiber;
        else if (t_mainfiber)
        return t_mainfiber;
        else return MainInit();
    };

    uint64_t Fiber::GetThisFiberId(){
        if (t_fiber){
            return t_fiber->m_id;
        }
        return -1;
    };

    void Fiber::YieldToHold(){
        if (t_fiber) {
            t_fiber->m_state = HOLD;
            t_fiber->swapOut();
        }
        else std::cerr << "YieldToHold: Not in child fiber!" << std::endl;
    };

    void Fiber::YieldToReady(){
        if (t_fiber) {
            t_fiber->m_state = READY;
            t_fiber->swapOut();
        }
        else std::cerr << "YieldToReady: Not in child fiber!" << std::endl;
    };

    void Fiber::MainFunc(){
        if (t_fiber) {
            t_fiber->m_cb();
            t_fiber->m_cb = nullptr;
            t_fiber->m_state = TERM;
            t_fiber->swapOut();
        }
        else std::cerr << "MainFunc: Not in child fiber!" << std::endl;
    };
}