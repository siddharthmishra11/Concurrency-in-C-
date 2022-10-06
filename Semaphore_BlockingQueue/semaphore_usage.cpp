#include<bits/stdc++.h>
#include<thread>
#include<unistd.h>
#include<mutex>
#include<unordered_map>
#include<chrono>
#include "semaphore.hpp"
using namespace std;
semaphore s(3);
void task(int j){
    s.wait();
    for(int i=0;i<5;i++){
        string str = "Task "+to_string(j)+" Completed\n";
        cout<<str;
        cout.flush();
        std::this_thread::sleep_for(std::chrono::seconds(3));
    }
    s.signal();
    
}
int main()
{   
    std::thread t1(task,1);
    std::thread t2(task,2);
    std::thread t3(task,3);
    std::thread t4(task,4);
    std::thread t5(task,5);
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
 } 
