#ifndef _FIBER_H_
#define _FIBER_H_

#include<ucontext.h>
#include<memory>
#include<functional>
#include<atomic>
#include"Thread.h"

namespace mycoroutine{

class Fiber : std::enable_shared_from_this<Fiber>{
public:
    enum State{
        HOLD,
        TERM,
        INIT,
        READY,
        EXEC,
    };
    static std::shared_ptr<Fiber> mainInit(){};

    static std::shared_ptr<Fiber> create(std::function<void()> cb, size_t stacksize);
    
    std::shared_ptr<Fiber> getShared(){
        return shared_from_this();
    }
    //reset the task of the fiber
    void reset(std::function<void()> cb); 
    void swapIn();
    void swapOut();
    //current fiber operations
    //TODO: SetThis to private or delete
    static void SetThis(std::shared_ptr<Fiber>);
    static uint64_t GetFiberId();
    static std::shared_ptr<Fiber> GetThis();
    static void YieldToHold();
    static void YieldToReady();
    static void MainFunc();
private:
    Fiber();
    Fiber(std::function<void()> cb, size_t stacksize);
    ~Fiber();

    uint64_t m_id;
    uint32_t m_stacksize;
    ucontext_t m_ctx;
    State m_state;
    void * m_stack = nullptr;
    std::function<void()> m_cb;
};
}

#endif