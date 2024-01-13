#include"src/mycoroutine.h"

void thisschduler(){
    while(1){
        std::cout << "scheduling..." << std::endl;
        std::cout << mycoroutine::GetFiberId() << std::endl;
        sleep(5);
    }
}

void cb(){
    for (int i = 0; i < 3; i ++){
        std::cout << "something..." <<std::endl;
        std::cout << mycoroutine::GetFiberId() <<std::endl;
        sleep(5);
    }
    mycoroutine::Fiber::YieldToHold();
};

using namespace std;
int main (){
    std::shared_ptr<mycoroutine::Fiber> mainfiber = mycoroutine::Fiber::MainInit();
    mainfiber->reset(&thisschduler);
    std::shared_ptr<mycoroutine::Fiber> fiber = mycoroutine::Fiber::Create(&cb, 16 * 1024);
    fiber->swapIn();
    cout << mycoroutine::GetFiberId() << endl;
    return 0;
}