#ifndef _MYCOROUTINE_THREAD_H_
#define _MYCOROUTINE_THREAD_H_

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
    ~Semaphore();
    void wait();
    void notify();
private:
    sem_t m_semaphore;
};

class myMutex{
public:
    myMutex(){
        pthread_mutex_init(&m_lock, NULL);
    };
    ~myMutex(){
        pthread_mutex_destroy(&m_lock);
    };
    void lock(){
        pthread_mutex_lock(&m_lock);
    };
    void unlock(){
        pthread_mutex_unlock(&m_lock);
    };
private:
    pthread_mutex_t m_lock;
};

class RWMutex{
public:
    RWMutex(){
        pthread_rwlock_init(&m_lock, NULL);
    };
    ~RWMutex(){
        pthread_rwlock_destroy(&m_lock);
    };
    void rdlock(){
        pthread_rwlock_rdlock(&m_lock);
    };
    void wrlock(){
        pthread_rwlock_wrlock(&m_lock);
    };
    void unlock(){
        pthread_rwlock_unlock(&m_lock);
    };
private:
    pthread_rwlock_t m_lock;
};

class MutexLock{
public: 
    MutexLock(myMutex& mutex) : m_mutex(mutex){
        m_mutex.lock();
        m_locked = true;
    };

    ~MutexLock(){
        unlock();
    };

    void lock(){
        if (!m_locked){
            m_mutex.lock();
            m_locked = true;
        }
    };

    void unlock(){
        if (m_locked){
            m_mutex.unlock();
            m_locked = false;
        }
    };
private:
    myMutex& m_mutex;
    bool m_locked;
};

class ReadLock{
public: 
    ReadLock(RWMutex& mutex) : m_mutex(mutex){
        m_mutex.rdlock();
        m_locked = true;
    };

    ~ReadLock(){
        unlock();
    };

    void lock(){
        if (!m_locked){
            m_mutex.rdlock();
            m_locked = true;
        }
    };

    void unlock(){
        if (m_locked){
            m_mutex.unlock();
            m_locked = false;
        }
    };
private:
    RWMutex& m_mutex;
    bool m_locked;
};

class WrLock{
public: 
    WrLock(RWMutex& mutex) : m_mutex(mutex){
        m_mutex.wrlock();
        m_locked = true;
    };

    ~WrLock(){
        unlock();
    };

    void lock(){
        if (!m_locked){
            m_mutex.wrlock();
            m_locked = true;
        }
    };

    void unlock(){
        if (m_locked){
            m_mutex.unlock();
            m_locked = false;
        }
    };
private:
    RWMutex& m_mutex;
    bool m_locked;
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
    ~Thread() = default;
};
}

#endif