#include<bits/stdc++.h>
#include<thread>
#include<unistd.h>
#include<mutex>
#include<chrono>
using namespace std;
// 0. std::try_lock() tries to lock all the mutexes passed in it one by one in given order.
// 1. On success this function returns -1 otherwise it will return 0-based mutex index number which it could not lock.
// 2. If it fails to lock any of the mutex then it will release all the mutex it locked before.
// 3. If a call to try_lock results in an exception, unlock is called for any locked objects before re-throwing.
int x = 0, y = 0;
mutex mx,my;
std::mutex m;
void take_rest(int x){
    std::this_thread::sleep_for(std::chrono::seconds(x));
}
void produce(int& var,std::mutex& m){
    for(int i=0;i<5;i++){
        m.lock();
        var++;
        m.unlock();
        take_rest(1);
    }
   
}
void consume(){
    int con = 0;
   
    while(1){
        if(std::try_lock(mx,my)==-1){
            if(x>0 && y>0){
                std::cout<<"Consumed "<<x<<" "<<y<<std::endl;
                x--;y--;
                con++;
            }
            mx.unlock();
            my.unlock();
        }
        if(con==5)break;
    }
}
int main()
{   
     std::thread t1(produce,std::ref(x),std::ref(mx));
     std::thread t2(produce,std::ref(y),std::ref(my));
     std::thread t3(consume);
    try{
        std::this_thread::sleep_for(chrono::seconds(3));
    }
    catch(...){
         t1.join();
         t2.join();
         t3.join();
        throw;
    }
    if(t1.joinable())t1.join();
    if(t2.joinable())t2.join();
    if(t3.joinable())t3.join();
 } 
