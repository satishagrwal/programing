#include <iostream>
#include <vector>
#include <mutex>
#include <memory>

template<typename T>
class ObjectPool{
    std::vector<std::unique_ptr<T>> pool;
    std::mutex mtx;
    size_t maxSize;
    
    public:
      ObjectPool() = default;
      ObjectPool(size_t size, size_t max) : maxSize(max){
          for(size_t i = 0; i< size; i++){
              pool.emplace_back(std::make_unique<T>());
          }
      }
      
     ObjectPool(const ObjectPool&) = delete;
     ObjectPool& operator=(const ObjectPool&) = delete;
     
     ObjectPool(ObjectPool&&) = delete;
     ObjectPool& operator=(ObjectPool&&) = delete;
      
      T* acquire(){
          std::lock_guard<std::mutex>lock(mtx);
          // If pool is empty
          if(pool.empty())
          {
              return new T();
          }
          
          std::unique_ptr<T> temp= std::move(pool.back());
          pool.pop_back();
          
          return temp.release();
          
      }
      
      void release(T* obj){
          std::lock_guard<std::mutex>lock(mtx);
          if(pool.size() < maxSize)
          {
              pool.emplace_back(std::unique_ptr<T>(obj));
          }
          else
          {
              delete obj;
          }
      }
      
      ~ObjectPool() = default;
};


class Connection{
   public:
    void connect() {
        std::cout << "connection" << std::endl;
    }
};

int main()
{
    ObjectPool<Connection> p(5, 10);
    Connection *c = p.acquire();
    
    c->connect();
    p.release(c);
    //c->connect();
    
    return 0;
}

