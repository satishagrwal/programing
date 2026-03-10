#include <iostream>
#include <mutex>

class Singleton
{
private:
    static Singleton* instance;
    static std::once_flag initFlag;

    Singleton() {}

public:

    static Singleton* getInstance()
    {
        std::call_once(initFlag, [](){
            instance = new Singleton();
        });

        return instance;
    }
    
    void logger(const std::string& msg)
    {
        std::cout << msg << std::endl;
    }
};

Singleton* Singleton::instance = nullptr;
std::once_flag Singleton::initFlag;

int main()
{
    Singleton::getInstance()->logger("Hello once flag singaleton class");
    return 0;
}
