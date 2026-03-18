#include <iostream>

template <typename T>
class UniquePtr {
private:
    T* m_ptr;

public:
    UniquePtr(T* ptr = nullptr) : m_ptr(ptr) {}

    ~UniquePtr() {
        delete m_ptr;
        std::cout << "Resource destroyed automatically\n";
    }

    UniquePtr(const UniquePtr&) = delete;
    UniquePtr& operator=(const UniquePtr&) = delete;

    UniquePtr(UniquePtr&& other) noexcept : m_ptr(other.m_ptr) {
        other.m_ptr = nullptr;
    }

    UniquePtr& operator=(UniquePtr&& other) noexcept {
        if (this != &other) {
            delete m_ptr;
            m_ptr = other.m_ptr;
            other.m_ptr = nullptr;
        }
        return *this;
    }

    T& operator*() const { return *m_ptr; }
    T* operator->() const { return m_ptr; }
    T* get() const { return m_ptr; }
/*
    T* release() {
        T* temp = m_ptr;
        m_ptr = nullptr;
        return temp;
    }
/*
};

// --- Testing ---
struct Task {
    void execute() { std::cout << "Task is running...\n"; }
};

int main() {
    UniquePtr<Task> ptr1(new Task());
    ptr1->execute();

    // UniquePtr<Task> ptr2 = ptr1; // ERROR: Copying is deleted!

    UniquePtr<Task> ptr2 = std::move(ptr1); // SUCCESS: Ownership moved to ptr2
    if (ptr1.get() == nullptr) {
        std::cout << "ptr1 is now empty.\n";
    }
    ptr2->execute();

    return 0;
} // ptr2 goes out of scope, Task is deleted
