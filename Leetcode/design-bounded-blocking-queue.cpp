class semaphore{
	const size_t semaphore_size;
	size_t available;
	std::mutex m;
	std::condition_variable cv;
public:
	//By default it is binary semaphore so default arg is 1
	explicit semaphore(const size_t& semaphore_size = 1):semaphore_size(semaphore_size),available(semaphore_size){}

	explicit semaphore(const size_t& available,const size_t& semaphore_size):semaphore_size(semaphore_size),available(available){}

	//Copy Constructor
	semaphore(const semaphore& s):semaphore_size(s.semaphore_size),available(s.available){};


    //Entry into Critical Section
	void wait(){
		std::unique_lock<std::mutex> ug(m);
		cv.wait(ug,[this]{return available>0;});
		this->available--;
	}

    //Exit Out of Critical Section
	void signal(){
		std::lock_guard<std::mutex> lg(m);
		this->available++;
		cv.notify_one();
	}

};
class BoundedBlockingQueue {
    semaphore full,empty,m;
    queue<int> q;
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