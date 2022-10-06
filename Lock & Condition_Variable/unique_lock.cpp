#include<bits/stdc++.h>
#include<thread>
#include<unistd.h>
#include<mutex>
#include<chrono>
using namespace std;
 
// 1. The class unique_lock is a mutex ownership wrapper.
// 2. It Allows:
//     a. Can Have Different Locking Strategies
//     b. time-constrained attempts at locking (try_lock_for, try_lock_until)
//     c. recursive locking
//     d. transfer of lock ownership (move not copy)
//     e. condition variables

// Locking Strategies
//    TYPE           EFFECTS(S)
// 1. defer_lock  do not acquire ownership of the mutex.
// 2. try_to_lock  try to acquire ownership of the mutex without blocking.
// 3. adopt_lock  assume the calling thread already has ownership of the mutex.

int buffer = 0;
std::mutex m;
void recursion1(int total){
     std::unqiue_lock<mutex> lock(m);
    for(int i=0;i<total;i++){
        buffer++;
    }
}
void recursion2(int total){
     std::unqiue_lock<mutex> lock(m,defer_lock);
     lock.lock();
    for(int i=0;i<total;i++){
        buffer++;
    }
}
void recursion3(int total){
    m.lock();
    std::unqiue_lock<mutex> lock(m,adapt_lock);
    for(int i=0;i<total;i++){
        buffer++;
    }
}
int main()
{    
    thread t1(recursion1,10000);
    thread t2(recursion1,10000);
    t1.join();
    t2.join();
    std::cout<<buffer<<std::endl;
 } 
