#include<bits/stdc++.h>
#include<thread>
#include<unistd.h>
#include<mutex>
#include<chrono>
using namespace std;
int critical_sec = 0;
std::mutex m;
void run(){
    std::this_thread::sleep_for(chrono::seconds(1));
    m.lock();
    ++critical_sec;
    m.unlock();
}
int main()
{   
     std::thread t1(run);
     std::thread t2(run);
    try{
        std::this_thread::sleep_for(chrono::seconds(3));
    }
    catch(...){
         t1.join();
         t2.join();
        throw;
    }
    if(t1.joinable())t1.join();
    if(t2.joinable())t2.join();
    std::cout<<critical_sec<<std::endl;
   
 } 
