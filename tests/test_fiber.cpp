#include"src/mycoroutine.h"

void thisschduler(){
    while(1){
        std::cout << "scheduling..." << std::endl;
        sleep(5);
    }
}

void cb(){
    std::cout << "something..." <<std::endl;
    std::cout << mycoroutine::GetFiberId() <<std::endl;
};

using namespace std;
int main (){
    std::shared_ptr<mycoroutine::Fiber> mainfiber = mycoroutine::Fiber::GetThis();
    mainfiber->reset(&thisschduler);
    std::shared_ptr<mycoroutine::Fiber> fiber = mycoroutine::Fiber::Create(&cb, 16 * 1024);
    fiber->swapIn();
    cout << mycoroutine::GetFiberId() << endl;
    mycoroutine::Fiber::YieldToHold();
    return 0;
}