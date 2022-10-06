#include<bits/stdc++.h>
#include<thread>
#include<unistd.h>
#include<mutex>
#include<condition_variable>
#include<unordered_map>
#include "../Semaphore_BlockingQueue/semaphore.hpp"
using namespace std;

class database{
    string data;
    semaphore wrt;
    std::mutex m;
    int rc;
public:
    database(){
        this->data = "";
        rc = 0;
    }
    void write(const string& s){
        wrt.wait();
        this->data += s;
        wrt.signal();
    }
    void read(){
        {

            lock_guard<mutex> lg(m);
            rc++;
            if(rc==1)wrt.wait();
        }
        string st = data+"\n";
        cout<<st;
        {
            lock_guard<mutex> lg(m);
            rc--;
            if(rc==0)wrt.signal();
        }
    }
};
int main()
{   
    database db;
    db.write("Naruto Best");
    db.write("\n One Piece Best");
    db.read();
    db.read();
    db.write(" Bleach is best");
    db.read();

} 
