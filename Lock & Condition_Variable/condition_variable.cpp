#include<bits/stdc++.h>
#include<thread>
#include<unistd.h>
#include<mutex>
#include<condition_variable>
#include<unordered_map>
using namespace std;
// 1. Condition variables allow us to synchronize threads via notifications.
//    a. notify_one();
//    b. notify_all();
// 2. You need mutex to use condition variable
// 3. Condition variable is used to synchronize two or more threads.
// 4. Best use case of condition variable is Producer/Consumer problem.
// 5. Condition variables can be used for two purposes:
//     a. Notify other threads
//     b. Wait for some condition
int balance = 0;
std::condition_variable cv;
std::mutex m;
void debit(int money){
    std::lock_guard<mutex> lg(m);
    balance += money;
    std::cout<<money<<" Debited"<<std::endl;
    cv.notify_one();
}
void credit(int money){
    std::unique_lock<mutex> ul(m);
    cv.wait(ul,[]{return balance>0?true:false;});
    if(money>balance){
        std::cout<<"Sorry "<<money<<" is more than the balance "<<balance<<std::endl;
    }
    else{
        balance -= money;
        std::cout<<money<<" Credited"<<std::endl;
    }
    std::cout<<"Current Balance "<<balance<<std::endl;
}
int main()
{    
    thread t2(credit,500);
    std::this_thread::sleep_for(std::chrono::seconds(3));
    thread t1(debit,1000);
    t1.join();
    t2.join();
     
} 
