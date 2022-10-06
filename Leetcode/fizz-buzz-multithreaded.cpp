class FizzBuzz {
private:
    int n;
    condition_variable cv;
    mutex m;
    int idx;
public:
    FizzBuzz(int n) {
        this->n = n;
        idx = 1;
    }

    // printFizz() outputs "fizz".
    void fizz(function<void()> printFizz) {
        while(idx<=n){
                unique_lock<mutex> ul(m);
                cv.wait(ul,[this]{return idx>n || (idx%5!=0 && idx%3==0);});
               if(idx<=n)
                printFizz();
                idx++;
                cv.notify_all();
        }
    }

    // printBuzz() outputs "buzz".
    void buzz(function<void()> printBuzz) {
      while(idx<=n){
        unique_lock<mutex> ul(m);
        cv.wait(ul,[this]{return idx>n || (idx%3!=0 && idx%5==0);});
        if(idx<=n)
        printBuzz();
        idx++;
        cv.notify_all();
      }
    }

    // printFizzBuzz() outputs "fizzbuzz".
	void fizzbuzz(function<void()> printFizzBuzz) {
      while(idx<=n){
        unique_lock<mutex> ul(m);
        cv.wait(ul,[this]{return idx>n || idx%15==0;});
           if(idx<=n)
              printFizzBuzz();
        idx++;
        cv.notify_all();
      }
    }

    // printNumber(x) outputs "x", where x is an integer.
    void number(function<void(int)> printNumber) {
      while(idx<=n){
        unique_lock<mutex> ul(m);
        cv.wait(ul,[this]{return idx>n || (idx%3!=0 && idx%5!=0);});
       if(idx<=n)
        printNumber(idx);
        idx++;
        cv.notify_all();
      }
       
    }
};