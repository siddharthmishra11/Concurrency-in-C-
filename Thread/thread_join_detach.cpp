#include<bits/stdc++.h>
#include<thread>
#include<unistd.h>
#include<mutex>
#include<chrono>
using namespace std;
//Join: Once a thread is started we wait for this thread to finish by calling join() method on thread object
void run(int x){
     
    while(x--)cout<<x<<endl;
   std::this_thread::sleep_for(chrono::seconds(3));
    std::cout<<"Thread Finished"<<std::endl;
}
int main()
{    
    std::thread t(run,10);
    std::cout<<"main()"<<std::endl;
    t.join();
    if(t.joinable())
        t.join();
     t.detach();
    std::this_thread::sleep_for(chrono::seconds(3));
    std::cout<<"main() after"<<std::endl;
   
    
 } 
