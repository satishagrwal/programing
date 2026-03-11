#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex m;
std::condition_variable cv;
int count = 1;

void printOdd()
{
    while(true)
    {
        std::unique_lock<std::mutex> lock(m);

        if(count > 20) break;

        cv.wait(lock, []{ return count % 2 == 1; });

        std::cout << "Odd : " << count++ << std::endl;

        cv.notify_all();
    }
}

void printEven()
{
    while(true)
    {
        std::unique_lock<std::mutex> lock(m);

        if(count > 20) break;

        cv.wait(lock, []{ return count % 2 == 0; });

        std::cout << "Even : " << count++ << std::endl;

        cv.notify_all();
    }
}

int main()
{
    std::thread t1(printOdd);
    std::thread t2(printEven);

    t1.join();
    t2.join();
}
