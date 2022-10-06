class Foo {
    mutex m;
    condition_variable cv;
    int turn;
public:
    Foo() {
        turn = 0;
    }
    void first(function<void()> printFirst) {
        
        // printFirst() outputs "first". Do not change or remove this line.
        unique_lock<mutex> ul(m);
        cv.wait(ul,[this]{return turn==0;});
        printFirst();
        turn = 1;
 
    }

    void second(function<void()> printSecond) {
        
        // printSecond() outputs "second". Do not change or remove this line.
        unique_lock<mutex> ul(m);
        cv.wait(ul,[this]{return turn==1;});
        printSecond();
        
    }

    void third(function<void()> printThird) {
        
        // printThird() outputs "third". Do not change or remove this line.
        unique_lock<mutex> ul(m);
        cv.wait(ul,[this]{return turn==1;});
        printThird();
      
    }
};