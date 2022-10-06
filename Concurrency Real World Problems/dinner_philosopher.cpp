#include<bits/stdc++.h>
#include<thread>
#include<unistd.h>
#include<mutex>
#include<condition_variable>
#include<unordered_map>
#include "../Semaphore_BlockingQueue/semaphore.hpp"
using namespace std;
#define N 5

semaphore** forks = new semaphore*[N]; 
//Only allow at max n-1 to eat
semaphore m(N-1);
void dinnerPhilosopherSoln_Allow_N_1(int idx){
    m.wait();
    forks[idx]->wait();
    forks[(idx+1)%N]->wait();
    string st = "Philospher Number "+to_string(idx)+" eat with forka "+to_string(idx)+" and "+to_string((idx+1)%N)+"\n";
    cout<<st;
    forks[idx]->signal();
    forks[(idx+1)%N]->signal();
    m.signal();
}
//Making the fork Acquring part critical section
std:: mutex mt;
void dinnerPhilosopherSoln_Fork_CS(int idx){
    {
            unique_lock<mutex> lg(mt);
            forks[idx]->wait();
            forks[(idx+1)%N]->wait();
    }
    string st = "Philospher Number "+to_string(idx)+" eat with forka "+to_string(idx)+" and "+to_string((idx+1)%N)+"\n";
    cout<<st;
    forks[idx]->signal();
    forks[(idx+1)%N]->signal();
     
}
//Odd Even Rule
//Odd Philospher will acquire idx+1 & then idx
///Even Philospher will acquire idx & then idx+1
void dinnerPhilosopherSolnOddEven(int idx){
    if(idx&1){
            forks[idx]->wait();
            forks[(idx+1)%N]->wait();
    }
    else{
        forks[(idx+1)%N]->wait();
        forks[idx]->wait();
    }
    string st = "Philospher Number "+to_string(idx)+" eat with forka "+to_string(idx)+" and "+to_string((idx+1)%N)+"\n";
    cout<<st;
    forks[idx]->signal();
    forks[(idx+1)%N]->signal();
    
}
int main()
{   
     //initialise fork mutex
     for(int i=0;i<N;i++)forks[i] = new semaphore;
     for(int i=0;i<N;i++)dinnerPhilosopherSolnOddEven(i);
    
} 
