#include<iostream>
#include<memory>

template <typename T>
class sharedPtr{
    T *ptr;
    int *refCount;
    
    void release(){
        if(ptr)
        {
            (*refCount)--;
            
            if(*refCount == 0)
            {
                delete ptr;
                delete refCount;
            }
        }
    }
    
    public: 
      sharedPtr(T *p = nullptr) : ptr(p){
          if(ptr){
              refCount = new int(1);
          }
          else{
             refCount = nullptr;   
          }
      }
      
      // copy constructor
      sharedPtr(const sharedPtr& rhs){
          ptr = rhs.ptr;
          refCount = rhs.refCount;
          
          if(refCount){
              (*refCount)++;
          }
     }
      
      // assignment operator
      sharedPtr& operator=(const sharedPtr& rhs){
          if(this != &rhs)
          {
              release();
              
              ptr = rhs.ptr;
              refCount = rhs.refCount;
              
              if(refCount){
                  (*refCount)++;
              }
          }
          return *this;
      }
     // move Constructor
    sharedPtr(sharedPtr&& rhs) noexcept{
          ptr = rhs.ptr;
          refCount = rhs.refCount;
          
          // source cleanup
          rhs.ptr = nullptr;
          rhs.refCount = nullptr;
     }
      
      // move assignment 
      sharedPtr& operator=(sharedPtr&& rhs) noexcept{
          if(this != &rhs)
          {
              release();
              
              ptr = rhs.ptr;
              refCount = rhs.refCount;
              
              // source cleanup
              rhs.ptr = nullptr;
              rhs.refCount = nullptr;  
          }
          return *this;
      }
      ~sharedPtr(){
          release();
      }
      
      int getCount(){
       if(ptr)
       {
         return *refCount;
       }
       else{
         return 0;
       }
     }
      
      T* operator->(){
          return ptr;
      }
      
      T& operator*(){
          return *ptr;
      }
};

int main()
{
    sharedPtr<int> ptr(new int());
    std::cout << ptr.getCount() << std::endl;
    
    {
        sharedPtr<int> ptr2 = ptr;
        std::cout << ptr.getCount() << std::endl;
    }
    std::cout << ptr.getCount() << std::endl;
    
    sharedPtr<int> ptr3 = std::move(ptr);
    std::cout << ptr3.getCount() << std::endl;
    return 0;
}
