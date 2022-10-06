#include<bits/stdc++.h>
#include<thread>
#include<unistd.h>
#include<mutex>
using namespace std;
void taskA(){
    for(int i=0;i<10;i++){
         sleep(1);
        std::printf("Task A:%d\n",i);
        std::fflush(stdout);
     
    }
}
void taskB(){
     for(int i=0;i<10;i++){
        sleep(1);
        std::printf("Task B:%d\n",i);
        std::fflush(stdout);
        
        
    }
}
int main()
{   
    std::thread t1(taskA);//child thread t1
    std::thread t2(taskB);
    t1.join();
    t2.join();
    t1.detach(); //becomes free of the main process -> daemon process
    t2.detach();

   once detached forever detached can't join again
    cout<<t1.joinable(); 
    try{
        for(int i=0;i<20;i++){
              sleep(1);
              std::printf("Task B:%d\n",i);
              std::fflush(stdout);
          }

    }catch(...){
              t1.join();
              throw;
        }
    t1.join();
    std::thread t(taskA);
    wrapper w(t);
    for(int i=0;i<20;i++){
              sleep(1);
              std::printf("Task B:%d\n",i);
              std::fflush(stdout);
          }
 } 
