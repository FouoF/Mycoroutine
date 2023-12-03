#ifndef _UTIL_H_
#define _UTIL_H_

#include<sys/unistd.h>
#include<syscall.h>

namespace mycoroutine{
    pid_t GetThreadId(){
        return syscall(SYS_gettid);
    }
}

#endif