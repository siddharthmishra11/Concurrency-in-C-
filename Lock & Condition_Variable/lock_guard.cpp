#include<bits/stdc++.h>
#include<thread>
#include<unistd.h>
#include<mutex>
#include<chrono>
using namespace std;
// 0. It is very light weight wrapper for owning mutex on scoped basis.
// 1. It acquires mutex lock the moment you create the object of lock_guard.
// 2. It automatically removes the lock while goes out of scope.
// 3. You can not explicitly unlock the lock_guard.
// 4. You can not copy lock_guard.

int buffer = 0;
std::mutex m;
void recursion(int total){
    for(int i=0;i<total;i++){
        std::lock_guard<mutex> lock(m);
        buffer++;
    }
}
int main()
{    
    thread t1(recursion,10000);
    thread t2(recursion,10000);
    t1.join();
    t2.join();
    std::cout<<buffer<<std::endl;
 } 
