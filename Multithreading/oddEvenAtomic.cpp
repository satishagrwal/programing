#include <iostream>
#include <thread>
#include <atomic>

std::atomic<int> count{1};

void printOdd()
{
    while(count <= 20)
    {
        if(count % 2 == 1)
        {
            std::cout << "Odd: " << count << std::endl;
            count++;
        }
    }
}

void printEven()
{
    while(count <= 20)
    {
        if(count % 2 == 0)
        {
            std::cout << "Even: " << count << std::endl;
            count++;
        }
    }
}

int main()
{
    std::thread t1(printOdd);
    std::thread t2(printEven);

    t1.join();
    t2.join();
}
