
#pragma once 
#include <queue>
#include <mutex>

template<typename _T>
class SafeQueue {
public:
    SafeQueue() {}
    ~SafeQueue() {}

    bool empty() {
        std::unique_lock<std::mutex> lock(mutex_);
        return queue_.empty();
    }

    int size() {
        std::unique_lock<std::mutex> lock(mutex_);
        return queue_.size();
    }

    void push(_T& t) {
        std::unique_lock<std::mutex> lock(mutex_);
        queue_.emplace(t);
    }

    void push(_T&& t) {
        std::unique_lock<std::mutex> lock(mutex_);
        queue_.emplace(std::move(t));
    }

    bool pop(_T& t) {
        std::unique_lock<std::mutex> lock(mutex_);
        if (queue_.empty()) {
            return false;
        }
        t = std::move(queue_.front());
        queue_.pop();  

        return true;  
    }

private:
    std::queue<_T> queue_;
    std::mutex mutex_;
};