#ifndef BLOCKING_QUEUE_HPP
#define BLOCKING_QUEUE_HPP

#include "semaphore.hpp"
#include <queue>
class BoundedBlockingQueue {
    semaphore full,empty,m;
    std::queue<int> q;
public:
    BoundedBlockingQueue(int capacity) {
        empty.~semaphore();
        new(&empty) semaphore(capacity);
        full.~semaphore();
        new(&full) semaphore(0,capacity);
    }
    
    void enqueue(int element) {
        empty.wait();
        m.wait();
        q.push(element);
        m.signal();
        full.signal();
    }
    
    int dequeue() {
        full.wait();
        m.wait();
        int ele = q.front();
        q.pop();
        m.signal();
        empty.signal();
        return ele;
        
    }
    
    int size() {
        return q.size();
    }
};

#endif