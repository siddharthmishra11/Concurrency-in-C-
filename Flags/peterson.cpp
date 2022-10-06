#include<bits/stdc++.h>
#include<thread>
#include<unistd.h>
#include<mutex>
using namespace std;
int cnt = 0;
int turn = 0;
bool flag[2] = {false,false};
void petersonSoln(int t){
for(int i=0;i<15000;i++)
 { 
    flag[t] = true;
    turn = t;
    while(flag[1-t] && turn==t);
    cnt++;
    flag[t] = false;
    
 }
}
int main()
{    
    std::thread t1(petersonSoln,0);
    std::thread t2(petersonSoln,1);
    t1.join();
    t2.join();
    printf("%d",cnt);
} 
