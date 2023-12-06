#ifndef _MYCOROUTINE_UTIL_H_
#define _MYCOROUTINE_UTIL_H_

#include<sys/unistd.h>
#include<syscall.h>

#include"fiber.h"

namespace mycoroutine{
    static pid_t GetThreadId(){
        return syscall(SYS_gettid);
    }

    static uint64_t GetFiberId(){
        return Fiber::GetThisFiberId();
    }
}

#endif