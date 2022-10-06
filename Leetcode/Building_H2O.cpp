class H2O {
    int h;
    condition_variable cv;
    mutex m;
public:
    H2O() {
        h = 0;
    }

    void hydrogen(function<void()> releaseHydrogen) {
        
        // releaseHydrogen() outputs "H". Do not change or remove this line.
        unique_lock<mutex> ul(m);
        cv.wait(ul,[this]{return h<2;});
        releaseHydrogen();
        h++;
        cv.notify_all();
    }

    void oxygen(function<void()> releaseOxygen) {
        
        // releaseOxygen() outputs "O". Do not change or remove this line.
        unique_lock<mutex> ul(m);
        cv.wait(ul,[this]{return h==2;});
        releaseOxygen();
        h = 0;
        cv.notify_all();
    }
};