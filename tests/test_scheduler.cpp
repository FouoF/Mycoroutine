#include"src/mycoroutine.h"

int main (){
    std::shared_ptr<mycoroutine::Scheduler> sc = std::make_shared<mycoroutine::Scheduler>();
    sc->start();
    sc->stop();
    return 0;
}