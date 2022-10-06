#include<bits/stdc++.h>
#include<thread>
#include<unistd.h>
#include<mutex>
#include<chrono>
using namespace std;
// 0. std::timed_mutex is blocked till timeout_time or the lock is aquired and returns true if success 
//    otherwise false.
// 1. Member Function:
//    a. lock 
//    b. try_lock
//    c. try_lock_for    ---\ These two functions makes it different from mutex.
//    d. try_lock_until  ---/ 
//    e. unlock

// EXAMPLE: try_lock_for();

//try_lock_for
std::timed_mutex m;
void run(int i){
    if(m.try_lock_for(std::chrono::seconds(2))){
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout<<"Thread "<<i<<" In"<<std::endl;
        m.unlock();
    }else{
        std::cout<<"Thread "<<i<<" Out"<<std::endl;
    }
}

//try_lock_until
void run2(int i){
    auto time = std::chrono::steady_clock::now();
    if(m.try_lock_until(time+std::chrono::seconds(1))){
        std::this_thread::sleep_for(std::chrono::seconds(2));
        std::cout<<"Thread "<<i<<" In"<<std::endl;
        m.unlock();
    }else{
        std::cout<<"Thread "<<i<<" Out"<<std::endl;
    }
}
int32_t main()
{   c_p_c();
    thread t1(run2,1);
    thread t2(run2,2);
    t1.join();
    t2.join();

 } 
