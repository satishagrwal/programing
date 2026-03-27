#include <iostream>
#include <mutex>
#include <vector>

template<typename T>
class objectPool
{
   private:
   
     std::vector<T*> pool;
     std::mutex mtx;
     size_t maxSize;
     
   public:
   
    objectPool(size_t size, size_t max) : maxSize(max){
        for(size_t i=0; i < size; i++)
        {
            pool.push_back(new T());
        }
    }
    
    ~objectPool(){
        for(auto obj: pool){
            delete obj;
        }   
    }
 
    ObjectPool(const ObjectPool&) = delete;
    ObjectPool& operator=(const ObjectPool&) = delete;

    ObjectPool(ObjectPool&&) = delete;
    ObjectPool& operator=(ObjectPool&&) = delete;

    T* acquire(){
        
        std::lock_guard<std::mutex> lock(mtx);
        
        // If pool is empty, return new object(fallback condition)
        if(pool.empty())
        {
            return new T();
        }
        
        T *obj = pool.back();
        pool.pop_back();
        
        return obj;
    }
    
    void release(T* obj){
        // Fallback scenario taken care here where caller received object that didn't come from pool
        // later when caller release, object will be pushed into pool.
        std::lock_guard<std::mutex> lock(mtx);
        
        if(pool.size() < maxSize)
        {
            pool.push_back(obj);
        }
        else{
            delete obj;
        }
    }
};

class connection
{
    public:
     void process(){
         std::cout << "Processing connection request" << std::endl;
     }
};


int main(){
    objectPool<connection> connPool(3, 5);
    
    connection* cP1 = connPool.acquire();
    cP1->process();
    
    connection* cP2 = connPool.acquire();
    cP2->process();
    
    connPool.release(cP1);
    connPool.release(cP2);
    
    return 0;
}
