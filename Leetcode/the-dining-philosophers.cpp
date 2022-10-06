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
class DiningPhilosophers {
  semaphore allowed{4};
  semaphore** fork = new semaphore*[5];
  mutex m;
public:
    DiningPhilosophers() {
        for(int i=0;i<5;i++)fork[i] = new semaphore;
    }

    void wantsToEat(int philosopher,
                    function<void()> pickLeftFork,
                    function<void()> pickRightFork,
                    function<void()> eat,
                    function<void()> putLeftFork,
                    function<void()> putRightFork) {
     
        allowed.wait();
        fork[philosopher]->wait();
        fork[(philosopher+1)%5]->wait();
        pickRightFork();
        pickLeftFork();
        eat();
        putLeftFork();
        fork[(philosopher+1)%5]->signal();
        putRightFork();
        fork[philosopher]->signal();
        allowed.signal();
    }
    
};