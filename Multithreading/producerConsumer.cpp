#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>

const int MAX_SIZE = 5;

std::mutex m;
std::condition_variable cv;
std::queue<int> buffer;

void producer()
{
    for(int i = 1; i <= 10; i++)
    {
        std::unique_lock<std::mutex> lock(m);

        cv.wait(lock, []{ return buffer.size() < MAX_SIZE; });

        buffer.push(i);
        std::cout << "Produced : " << i << std::endl;

        cv.notify_one();
    }
}

void consumer()
{
    for(int i = 1; i <= 10; i++)
    {
        std::unique_lock<std::mutex> lock(m);

        cv.wait(lock, []{ return !buffer.empty(); });

        int item = buffer.front();
        buffer.pop();

        std::cout << "Consumed : " << item << std::endl;

        cv.notify_one();
    }
}

int main()
{
    std::thread t1(producer);
    std::thread t2(consumer);

    t1.join();
    t2.join();

    return 0;
}
