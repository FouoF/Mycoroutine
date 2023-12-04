#ifndef _THREAD_H_
#define _THREAD_H_

#include<thread>
#include<functional>
#include<pthread.h>
#include<memory>
#include<iostream>
#include<semaphore.h>

#include"noncopyable.h"

namespace mycoroutine{
class Semaphore{
public:
    Semaphore(uint32_t count = 0);
    void wait();
    void notify();
private:
    sem_t m_semaphore;
};

class Mutex{
public:
    Mutex(){
        pthread_mutex_init(&m_lock, NULL);
    }
    ~Mutex(){
        pthread_mutex_unlock(&m_lock);
        pthread_mutex_destroy(&m_lock);
    }
    void lock(){
        pthread_mutex_lock(&m_lock);
    }
    void unlock(){
        pthread_mutex_unlock(&m_lock);
    }
private:
    pthread_mutex_t m_lock;
};

class RWMutex{
public:
    RWMutex(){
        pthread_rwlock_init(&m_lock, NULL);
    }
    ~RWMutex(){
        pthread_rwlock_destroy(&m_lock);
    }
    void rdlock(){
        pthread_rwlock_rdlock(&m_lock);
    }
    void wrlock(){
        pthread_rwlock_wrlock(&m_lock);
    }
    void unlock(){
        pthread_rwlock_unlock(&m_lock);
    }
private:
    pthread_rwlock_t m_lock;
};

class Thread:noncopyable
{
private:
    pid_t m_id;
    pthread_t m_thread;
    std::function<void()> m_cb;
    std::string m_name;
    Semaphore m_semaphore;
public:
    typedef std::shared_ptr<Thread> ptr;
    Thread(std::function<void()> cb, std::string name);
    pid_t getId() const {return m_id;};
    const std::string getName() const {return m_name;};

    void join();
    static void * run(void * arg);
    static const std::string GetName();
    static Thread* GetThis();
    static void SetName(const std::string);
    ~Thread();
};
}

#endif