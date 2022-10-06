#include<bits/stdc++.h>
#include<thread>
#include<unistd.h>
#include<mutex>
#include<chrono>
using namespace std;
//5 ways to create Thread
//1.functors
//2.Lambda Functions
//3.Functor
//4.Member Functions
//4.Static Member Functions
typedef unsigned long long ull;
using namespace chrono;
ull oddSum = 0;
ull evenSum = 0;
void findEvenSum(ull start, ull end){
    for(ull i=start;i<=end;i++){
        if((i&1)==0)
            evenSum += i;
    }
}
void findOddSum(ull start, ull end){
    for(ull i=start;i<=end;i++){
        if(i&1)
            oddSum += i;
    }
}
//Functor : class with overloading of () operator
class base{
public: 
    void operator()(int x){
         while(x--)std::cout<<x<<std::endl;
    }
    void run(int x){
         while(x--)std::cout<<x<<std::endl;
    }
    static void done(int x){
        while(x--)std::cout<<x<<std::endl;
    }
};
int main()
{  
    ull start = 0, end = 1900000000;
    auto startTime =  std::chrono::high_resolution_clock::now();
    findOddSum(start,end);
    findEvenSum(start,end);
    auto endTime = std::chrono::high_resolution_clock::now();
    auto time = duration_cast<microseconds>(endTime-startTime);
    std::cout<<"Single threading"<<std::endl;
    std::cout<<"Odd Sum: "<<oddSum<<std::endl;
    std::cout<<"Even Sum: "<<oddSum<<std::endl;
    std::cout<<"Seconds "<<time.count()*1ll/1000000<<std::endl;
    oddSum = evenSum = 0;
    startTime =  high_resolution_clock::now();
    std::thread t1(findOddSum,start,end);
    std::thread t2(findEvenSum,start,end);
    t1.join();
    t2.join();
    endTime = high_resolution_clock::now();
    time = duration_cast<microseconds>(endTime-startTime);
    std::cout<<"Multi threading"<<std::endl;
    std::cout<<"Odd Sum: "<<oddSum<<std::endl;
    std::cout<<"Even Sum: "<<oddSum<<std::endl;
    std::cout<<"Seconds "<<time.count()*1ll/1000000<<std::endl;

    //Thread Creation Using Lambda
    auto fn = [](int x){
        while(x--)cout<<x<<endl;
    };
    std::thread t(fn,10);
    std:: thread t3([](int x){
        while(x--)cout<<x<<endl;
    },20);
    t.join();
    t3.join();
    Functors
    std:: thread t4(base(),10);
    t4.join();
    base b;
    thread t5(base::run,&b,10);
    t5.join();
     thread t6(base::done,10);
     t6.join();
    
 } 
