#include <iostream>
#include<memory>
#include<string>
#include <mutex>
#include <vector>
#include <chrono>
#include<thread>

using namespace std;

class callInfo;

class callState{
    public:
    
     virtual void sendInvite(callInfo& info){ log("sendInvite not allowed in this state");}
     virtual void recv180(callInfo& info) { log("recv180 not allowed in this state" );}
     virtual void recv200(callInfo& info) { log("recv200 not allowed in this state" );}
     virtual void sendAck(callInfo& info) { log("sendAck not allowed in this state");}
     virtual void sendBye(callInfo& info) { log("recvBye not allowed in this state" );}
     virtual void recvBye(callInfo& info) { log("recvBye not allowed in this state");}
     virtual ~callState() = default;
     
     protected:
       void log(const std::string& msg){ std::cout << msg << std::endl;}
};

class Idle : public callState{
    void sendInvite(callInfo& info) override;
};

class callInitiate : public callState{
    virtual void recv180(callInfo& info) override;
};

class callRinging : public callState{
    virtual void recv200(callInfo& info) override;
    
};

class callEstablished : public callState{
    void sendBye(callInfo& info) override;
    void recvBye(callInfo& info) override;
};

class callTerminate : public callState{
    public:
     callTerminate(){std::cout << "Call terminated" << std::endl;}
};

class callInfo{
  std::unique_ptr<callState> state;
  std::mutex mtx;
  
  public:
  
   void setState(std::unique_ptr<callState> s){
       //std::lock_guard<std::mutex> lock(mtx);
       state = std::move(s);
   }
   
   callInfo() {
       state = std::make_unique<Idle>();
   }
   // events
   void sendInvite(){
       std::lock_guard<std::mutex> lock(mtx);
       state -> sendInvite(*this);
   }
   void recv180() {
       std::lock_guard<std::mutex> lock(mtx);
       state -> recv180(*this);
   }
   
   void recv200() {
       std::lock_guard<std::mutex> lock(mtx);
       state -> recv200(*this); 
   }
   
   void sendAck() {
       std::lock_guard<std::mutex> lock(mtx);
       state -> sendAck(*this);
    }
    
   void sendBye() { 
       std::lock_guard<std::mutex> lock(mtx);
       state -> sendBye(*this); 
   }
   
   void recvBye() {
       std::lock_guard<std::mutex> lock(mtx);
       state -> recvBye(*this); 
   }
};

void Idle::sendInvite(callInfo& call){
    std::cout << "Sending INVITE" << std::endl;
    call.setState(std::make_unique<callInitiate>());
}

void callInitiate::recv180(callInfo& call){
    std::cout << "Receiving 180 Ringing" << std::endl;
    call.setState(std::make_unique<callRinging>());
}

void callRinging::recv200(callInfo& call){
    std::cout << "Receiving 200 OK" << std::endl;
    call.setState(std::make_unique<callEstablished>());
}

void callEstablished::sendBye(callInfo& call){
    std::cout << "Sending BYE" << std::endl;
    call.setState(std::make_unique<callTerminate>());
}

void callEstablished::recvBye(callInfo& call){
    std::cout << "Receiving BYE" << std::endl;
    call.setState(std::make_unique<callTerminate>());
}


void threadInvite(callInfo& call)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    call.sendInvite();
}

void thread180(callInfo& call)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    call.recv180();
}

void thread200(callInfo& call)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(150));
    call.recv200();
}

void threadBye(callInfo& call)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    call.sendBye();
}


int main(){
    callInfo call;
    std::vector<std::thread> threads;
   /*
    // emplace_back constructs the object directly inside the vector.
    threads.emplace_back(threadInvite, std::ref(call));
    threads.emplace_back(thread180, std::ref(call));
    threads.emplace_back(thread200, std::ref(call));
    threads.emplace_back(threadBye, std::ref(call));
    */
    
    // A temporary std::thread object is created, then moved into the vector
    threads.push_back(std::thread(threadInvite, std::ref(call)));
    threads.push_back(std::thread(thread180, std::ref(call)));
    threads.push_back(std::thread(thread200, std::ref(call)));
    threads.push_back(std::thread(threadBye, std::ref(call)));

    for (auto& t : threads)
        t.join();
        
    return 0;
}
