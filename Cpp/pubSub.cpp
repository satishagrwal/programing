#include<iostream>
#include<vector>
#include <algorithm>


class Subscriber{
  public:
    virtual void update(int data) = 0;
    virtual ~Subscriber() = default;
};

class Publisher{
    private:
       std::vector<Subscriber*> subs;
       
    public:
       void subscribe(Subscriber* sub){
           auto it = std::find(subs.begin(), subs.end(), sub);
           
           // If subscriber not found then only push to the list
           if(it == subs.end())
              subs.push_back(sub);
       }
       
       void unSubscribe(Subscriber* sub){
           auto it = std::find(subs.begin(), subs.end(), sub);
           
          // If subscriber found then only removed from list
          if(it != subs.end()) 
              subs.erase(it);
        }
       
       void notify(int data){
           for(auto& s : subs){
               s->update(data);
           }
       }
};

class concreteSubscriber : public Subscriber{
    public:
      void update(int data) override{
          std::cout << "Received udpate : " << data << std::endl;
      }
};



int main(){
    Publisher pub;
    
    concreteSubscriber s1;
    concreteSubscriber s2;
    
    pub.subscribe(&s1);
    pub.subscribe(&s1);
    pub.subscribe(&s2);
    
    pub.notify(50);
    
    pub.unSubscribe(&s1);
    
    pub.notify(100);
    
    
    return 0;
}
