#include"scheduler.h"

namespace mycoroutine{

static thread_local Scheduler * t_scheduler = nullptr;
static thread_local Fiber * t_fiber = nullptr;

Scheduler(size_t thread_num = 1, bool use_caller = true, std::string name = "DEFAULT"){

}; 
virtual ~Scheduler(){
    
};

std::shared_ptr<Scheduler> Scheduler::GetThis(){

};
std::shared_ptr<Fiber> Scheduler::GetMainFiber(){

};

void Scheduler::start(){

};
void Scheduler::stop(){

};
}