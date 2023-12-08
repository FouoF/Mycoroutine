#ifndef _MYCOROUTINE_FIBER_H_
#define _MYCOROUTINE_FIBER_H_

#include<ucontext.h>
#include<memory>
#include<functional>
#include<atomic>

#include"thread.h"

namespace mycoroutine{

class Fiber : public std::enable_shared_from_this<Fiber>{
public:
    Fiber();
    ~Fiber();
    enum State{
        HOLD,
        TERM,
        INIT,
        READY,
        EXEC,
    };
    static std::shared_ptr<Fiber> MainInit();

    static std::shared_ptr<Fiber> Create(std::function<void()> cb, size_t stacksize);

    Fiber(std::function<void()> cb, size_t stacksize);
    
    std::shared_ptr<Fiber> getShared(){
        return shared_from_this();
    };
    State getState(){
        return m_state;
    };
    void setState(State state){
        m_state = state;
    };
    //reset the task of the fiber
    void reset(std::function<void()> cb); 
    void swapIn();
    void swapOut();
    //current fiber operations
    //TODO: SetThis to private or delete
    static void SetThis(std::shared_ptr<Fiber>);
    static uint64_t GetThisFiberId();
    static std::shared_ptr<Fiber> GetThis();
    static void YieldToHold();
    static void YieldToReady();
    static void MainFunc();
private:
    std::function<void()> m_cb = nullptr;
    uint64_t m_id = 0;
    uint32_t m_stacksize = 0;
    ucontext_t m_ctx;
    State m_state;
    void * m_stack = nullptr;
};
}

#endif