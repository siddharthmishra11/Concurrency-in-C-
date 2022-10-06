class FooBar {
private:
    int n;
    mutex m;
    int turn;
    condition_variable cv;
public:
    FooBar(int n) {
        this->n = n;
        turn = 0;
    }

    void foo(function<void()> printFoo) {
        
        for (int i = 0; i < n; i++) {
            
        	// printFoo() outputs "foo". Do not change or remove this line.
        
           unique_lock<mutex> ul(m);
           cv.wait(ul,[this]{return turn==0;});
           printFoo();
           turn ^= 1;
           cv.notify_one();
        }
    }

    void bar(function<void()> printBar) {
        
        for (int i = 0; i < n; i++) {
            
        	// printBar() outputs "bar". Do not change or remove this line.
           unique_lock<mutex> ul(m);
           cv.wait(ul,[this]{return turn==1;});
           printBar();
           turn ^= 1;
           cv.notify_one();
        }
    }
};