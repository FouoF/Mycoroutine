#include"src/mycoroutine.h"

void thisschduler(){
    int c = 0;
    while(1){
        std::cout << "scheduling... : " << c++ << std::endl;
    }
}

void cb(){
    for (int i = 0; i < 3; i ++){
        std::cout << "something..." <<std::endl;
    }
    mycoroutine::Fiber::YieldToHold();
};

using namespace std;
int main (){
    std::shared_ptr<mycoroutine::Fiber> mainfiber = mycoroutine::Fiber::MainInit();
    mainfiber->reset(&thisschduler);
    std::shared_ptr<mycoroutine::Fiber> fiber = mycoroutine::Fiber::Create(&cb, 16 * 1024);
    fiber->swapIn();
    return 0;
}