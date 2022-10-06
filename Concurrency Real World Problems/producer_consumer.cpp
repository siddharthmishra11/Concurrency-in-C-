#include<bits/stdc++.h>
#include<thread>
#include<unistd.h>
#include<mutex>
#include<condition_variable>
#include<unordered_map>
#include "../Semaphore_BlockingQueue/semaphore.hpp"
using namespace std;
int item = 0;
std::deque<int> buffer;
const unsigned int maxBufferSize = 50;
semaphore m;
semaphore empty(maxBufferSize);
semaphore filling(0,maxBufferSize);
void producer(int val){
    empty.wait();
    m.wait();
    buffer.push_back(val);
    string st = to_string(val)+" pushed into bounded buffer\n";
    std::cout<<st;
    m.signal();
    filling.signal();
}
void consumer(){
    filling.wait();
    m.wait();
    string st = to_string(buffer.back())+" consumed from bounded buffer\n";
    std::cout<<st;
    buffer.pop_back();
    m.signal();
    empty.signal();
}
int main()
{    

    std::thread t1(consumer);
    std::thread t2(producer,0);
    std::thread t3(consumer);
    std::thread t4(consumer);
    std::thread t5(producer,1);
    std::thread t6(producer,7);
    std::thread t7(producer,9);
    std::thread t8(producer,6);

    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    t6.join();
    t7.join();
    t8.join();
} 
