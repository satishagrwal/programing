#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <atomic>


class JitterBuffer {
    std::vector<int> buffer;
    size_t size;
    std::atomic<size_t> head{0};  // Producer index
    std::atomic<size_t> tail{0};  // Consumer index
    const size_t threshold;       // Minimum fill to start playout(50%)
    bool isBuffering = true;      // Added to handle start-up logic

public:
    JitterBuffer(size_t n) : buffer(n), size(n), threshold(n / 2) {}

    // Called by Network Thread (Producer)
    bool push(int packet) {
        size_t h = head.load(std::memory_order_relaxed);
        size_t next_h = (h + 1) % size;

        if (next_h == tail.load(std::memory_order_acquire)) 
            return false; // Buffer Full (Overflow)

        buffer[h] = packet;
        head.store(next_h, std::memory_order_release);
        return true;
    }

    // Called by Playback Thread (Consumer)
    bool pull(int& outData) {
        size_t t = tail.load(std::memory_order_relaxed);
        size_t h = head.load(std::memory_order_acquire);

        // Buffer Empty (Underflow)
        if (h == t) 
        {
            isBuffering = true; // Ran dry, must re-buffer
            return false;       
        }

        // Check for pre-buffering threshold
        size_t fill = (h - t + size) % size;
        
        // Only block if we are in buffering mode
        if(isBuffering)
        {
           if (fill < threshold)
           {
              return false; 
           }
           isBuffering = false; // Threshold reached!
        }
        
        outData = buffer[t];
        tail.store((t + 1) % size, std::memory_order_release);
        return true;
    }
};

void producer(JitterBuffer& jb) {
    for (int i = 1; i <= 20; ++i) {
        if (jb.push(i)) {
            std::cout << "[Producer] Pushed: " << i << std::endl;
        } else {
            std::cout << "[Producer] Buffer Full! Dropped: " << i << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}

void consumer(JitterBuffer& jb, std::vector<int>& results) {
        int data;
        int consumedCount = 0;
        
        // Try to consume 20 packets
        while (consumedCount < 15) { 
            if (jb.pull(data)) {
                std::cout << "    [Consumer] Pulled: " << data << std::endl;
                results.push_back(data);
                consumedCount++;
            } else {
                // Buffer empty or below threshold
                std::this_thread::sleep_for(std::chrono::milliseconds(30));
            }
        }
}

int main() {
    const size_t BUFFER_CAPACITY = 10;
    JitterBuffer jb(BUFFER_CAPACITY);
    std::vector<int> receivedData;

    // 1. PRODUCER THREAD: Simulates incoming network packets
    std::thread pThread(producer, std::ref(jb));

    // 2. CONSUMER THREAD: Simulates incoming network packets to consume
    std::thread cThread(consumer, std::ref(jb), std::ref(receivedData));

    pThread.join();
    cThread.join();

    std::cout << "\nVerification Complete. Total packets processed: " << receivedData.size() << std::endl;
    return 0;
}
