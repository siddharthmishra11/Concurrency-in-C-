#include<bits/stdc++.h>
#include<thread>
#include<unistd.h>
#include<mutex>
using namespace std;
int cnt = 0;
int turn = 0;
//Flag based Solution with No progress 
void taskD(int t){
    for(int i=0;i<15000;i++)
        { 
             while(turn!=t);
               cnt++;  
             turn = 1-t;
        }
  

}
int main()
{   
    thread t1(taskD,0);
    thread t2(taskD,1);
    t1.join();
    t2.join();
    printf("%d",cnt);
} 
