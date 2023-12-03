#include"Thread.h"
#include"util.h"

namespace mycoroutine{
static thread_local Thread* t_thread = nullptr;
static thread_local std::string t_thread_name = "DEFAULT";

Semaphore::Semaphore(uint32_t count){
    if (sem_init(&m_semaphore, 0, count)) {
        std::cerr << "semaphore init failed!" << std::endl;
    }
}

Semaphore::~Semaphore(){
    sem_destroy(&m_semaphore);
}

void Semaphore::wait(){
    if (sem_wait(&m_semaphore)) 
    std::cerr << "semaphore wait meet unknow error!" << std::endl;
}

void Semaphore::notify(){
    if (sem_post(&m_semaphore))
    std::cerr << "semaphore post failed!" << std::endl;
}

Thread* Thread::GetThis(){
    return t_thread;
}

const std::string Thread::GetName(){
    return t_thread_name;
}

void Thread::SetName(const std::string name){
    if (t_thread){
        t_thread->m_name = name;
    }
    t_thread_name = name;
}

Thread::Thread(std::function<void()> cb, std::string name){
    if (name.empty()) this->m_name = "DEFAULT";
    this->m_cb = cb;
    if(pthread_create(&m_thread, nullptr, Thread::run, this)) 
    std::cerr << "thread create fail!" << std::endl;
    m_semaphore.wait();
};

void Thread::join(){
    if (m_thread) {
       if(pthread_join(m_thread, nullptr)) std::cerr << "join failed!" << std::endl;
    }
}
Thread::~Thread(){
    if (m_thread) pthread_detach(m_thread);
}

void * Thread::run(void * arg){
    Thread * thread = (Thread *)arg;
    t_thread = thread;
    thread->m_id = GetThreadId();
    pthread_setname_np(pthread_self(), thread->m_name.substr(0, 15).c_str());
    std::function<void()> cb;
    cb.swap(thread->m_cb);
    thread->m_semaphore.notify();
    cb();
    return 0;
}
}