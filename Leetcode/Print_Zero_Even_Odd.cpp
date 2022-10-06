class ZeroEvenOdd {
private:
    int n;
    int turn;
    int x;
    mutex m;
    condition_variable cv;
public:
    ZeroEvenOdd(int n) {
        this->n = n;
        turn = 0;
        x = 1;
    }

    // printNumber(x) outputs "x", where x is an integer.
    void zero(function<void(int)> printNumber) {
      while(x<=n){
        unique_lock<mutex> ul(m);
        cv.wait(ul,[this]{return x>n || turn==0;});
        if(x<=n)
        printNumber(0);
        turn = x%2?2:1;
        cv.notify_all();
      }
    }

    void even(function<void(int)> printNumber) {
        while(x<=n){
        unique_lock<mutex> ul(m);
        cv.wait(ul,[this]{return x>n || (turn==1);});
        if(x<=n)
        printNumber(x);
        x++;
        turn = 0;
        cv.notify_all();
      }
    }

    void odd(function<void(int)> printNumber) {
        while(x<=n){
        unique_lock<mutex> ul(m);
        cv.wait(ul,[this]{return x>n || (turn==2);});
        if(x<=n)
        printNumber(x);
        x++;
        turn = 0;
        cv.notify_all();
      }
    }
};