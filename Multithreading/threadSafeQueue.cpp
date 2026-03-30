#include <iostream>
#include <queue>
#include <mutex>
#include <thread>

class ThreadSafeQueue {
    std::mutex mtx;
    std::queue<int> q;

public:

    void push(int v) {
        std::lock_guard<std::mutex> lock(mtx);
        q.push(v);
    }

    bool pop(int &item) {
        std::lock_guard<std::mutex> lock(mtx);

        if (q.empty())
            return false;

        item = q.front();
        q.pop();
        return true;
    }
};

int main() {

    ThreadSafeQueue q;

    std::thread t1(&ThreadSafeQueue::push, &q, 3);

    std::thread t2([&q](){
        int val;
        if(q.pop(val))
            std::cout << val << std::endl;
    });

    t1.join();
    t2.join();

    return 0;
}
