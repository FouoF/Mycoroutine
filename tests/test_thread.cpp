#include"src/mycoroutine.h"
#include<iostream>

int c;
using namespace std;
mycoroutine::myMutex mutex;
void cb(){
    for (int i = 0; i < 10000; i++){
        cout << c++ << " ";
        cout << mycoroutine::GetThreadId() << endl;
    }
}

int main (){
    vector<mycoroutine::Thread::ptr> threads;
    for (int i = 0; i < 5; i ++){
        mycoroutine::Thread::ptr thread(new mycoroutine::Thread(&cb, to_string(i)));
        threads.push_back(thread);
    }
    for (int i = 0; i < 5; i++){
          threads[i]->join();
    }
    sleep(5);
    return 0;
}