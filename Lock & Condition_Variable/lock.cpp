#include<bits/stdc++.h>
#include<thread>
#include<unistd.h>
#include<mutex>
using namespace std;
int cnt = 0;
//Lock Based Solution to Race Condition
mutex l;
void taskC(){

    for(int i=0;i<150000;i++)
            {
                l.lock();
                cnt++;
                l.unlock();
            }
        
    
}
 

int main()
{    
    thread t1(taskC);
    thread t2(taskC);
    t1.join();
    t2.join();
    printf("%d",cnt);
} 
