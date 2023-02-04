
#pragma once 
#include <functional>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>

/**
 * @brief: 多队列线程池的安全队列
 * @details: 
 * @return {*}
 */
template<typename _T>
class MultipleSafeQueue {
public:
    MultipleSafeQueue() {}
    ~MultipleSafeQueue() {}

    bool empty() {
        std::lock_guard<std::mutex> lock(mt_);
        return queue_.empty();
    }

    int size() {
        std::lock_guard<std::mutex> lock(mt_);
        return queue_.size();
    }

    void push(_T& t) {
        {
            std::lock_guard<std::mutex> lock(mt_); 
            queue_.push(t);
        }
        cond_.notify_one();  
    }

    void push(_T&& t) {
        {
            std::lock_guard<std::mutex> lock(mt_); 
            queue_.push(std::move(t));
        }
        cond_.notify_one();  
    }

    bool pop(_T& t) {
        std::unique_lock<std::mutex> lock(mt_);   // 不能用lock_guard, 条件变量要和unique_lock 配合使用  
        cond_.wait(lock, [&]() {
            return !queue_.empty() || stop_; 
        });
        // 如果stop_ = true 那么退出
        if (queue_.empty()) {
            return false;
        }

        t = std::move(queue_.front());
        queue_.pop();  

        return true;  
    }

    void stop() {
        stop_ = true;
        cond_.notify_one();  
    }

private:
    std::queue<_T> queue_;
    std::mutex mt_;
    std::condition_variable cond_;
    bool stop_ = false;
};

// 多任务队列线程池
class MultipleThreadPool {
public:
    using WorkItem = std::function<void()>;  

    explicit MultipleThreadPool(const size_t n = std::thread::hardware_concurrency()) 
        : threads_(n), task_queue_(n), shutdown_(false) {
        auto worker = [this](size_t id) {   // id 表示该任务指定由哪个线程完成
            while (true) {
                WorkItem task;
                // 如果任务队列为空  则会在这里阻塞，直到有新的任务，线程池关闭时，pop()会return false，从而退出该线程
                if (!task_queue_[id].pop(task)) {
                    std::cout << "*" << std::endl;
                    break;  
                }
                task();  
            }
        };
        std::cout << "thread num: " << threads_.size() << std::endl;
        // 分配工作线程  
        for (int i = 0; i < threads_.size(); ++i) {
            threads_.at(i) = std::thread(worker, i);      // 线程启动 
        }
        std::cout << "MultipleThreadPool construct" << std::endl;
    }

    ~MultipleThreadPool() {
        std::cout << "~MultipleThreadPool()" << std::endl;
        // 停止每一个任务队列
        for (auto& queue : task_queue_) {
            queue.stop();
        }
        // 等待每一个线程执行结束
        for (auto& t : threads_ ) {
            t.join();   
        }
        std::cout << "shutdown !" << std::endl;
    }

    /**
     * @brief: 注册一个任务 
     * @param f 任务函数 
     * @param args 参数数据  
     * @return {*}
     */    
    template<typename _F, typename... _Args>
    auto submit(_F&& f, _Args&&... args) -> std::future<decltype(f(args...))> {    // 尾返回    
        // 绑定任何 返回值为 decltype(f(args...)) , 行参为 ()的函数  
        std::function<decltype(f(args...))()> func = std::bind(std::forward<_F>(f), std::forward<_Args>(args)...);
        /**
         * @todo 将task_ptr 该为非指针
         */
        auto task_ptr = std::make_shared<std::packaged_task<decltype(f(args...))()>>(func); // packaged_task封装func用于异步调用
        // function 对 lamda表达时进行包装
        WorkItem warpper_func = [task_ptr]() {
            (*task_ptr)();
        };
        size_t id = rand() % threads_.size();     
        task_queue_[id].push(std::move(warpper_func));   // 随机压入到一个任务队列中   
        return task_ptr->get_future();  // 这个future绑定了func 的返回值  通过 .get() 可以获取该返回值  
    }

private:
    bool shutdown_; 
    std::mutex conditional_mutex_; 
    std::vector<MultipleSafeQueue<WorkItem>> task_queue_;   // 每个线程分配一个任务队列  
    // 工作线程队列
    std::vector<std::thread> threads_;
};