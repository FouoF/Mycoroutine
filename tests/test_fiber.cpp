#include"src/mycoroutine.h"

void schduler(){
    while(1){
        sleep(5);
    }
}

void cb(){
    std::cout << "something..." <<std::endl;
};

int main (){
    std::shared_ptr<mycoroutine::Fiber> mainfiber = mycoroutine::Fiber::GetThis();
    std::shared_ptr<mycoroutine::Fiber> fiber = mycoroutine::Fiber::Create(&cb, 64);
    fiber->swapIn();
    mycoroutine::Fiber::YieldToHold();
    return 0;
}