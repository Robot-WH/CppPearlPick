#pragma once 
#include <functional>
#include <thread>
#include <condition_variable>
#include <future>
#include "safe_queue.hpp"

class ThreadPool {
public:
    // 默认的线程数量为 4 
    ThreadPool(const int n = 4) : threads_(std::vector<std::thread>(n)), shutdown_(false) {
        // 分配工作线程  
        for (int i = 0; i < threads_.size(); ++i) {
            threads_.at(i) = std::thread(ThreadWorker(this, i));      // 线程启动  执行  ThreadWorker() 
        }
    }

    void shutdown() {
        // 唤醒所有的线程
        shutdown_ = true; 
        condition_lock_.notify_all();    // 可能有任务在wait()等待呢，这里将其唤醒，以备其线程退出  
        // 等待每个线程都执行完毕了 才shutdown 
        for (int i = 0; i < threads_.size(); ++i) {
            // 如果已经join()或者detach()   那么joinable() 为false
            if (threads_.at(i).joinable()) {
                threads_.at(i).join();   // 等待线程结束
            }
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
        std::function<void()> warpper_func = [task_ptr]() {
            (*task_ptr)();
        };
        task_queue_.push(warpper_func);   // 压入到任务队列中   
        condition_lock_.notify_one();    // 通知别的线程来领取任务  
        return task_ptr->get_future();  // 这个future绑定了func 的返回值  通过 .get() 可以获取该返回值  
    }

private:
    //内置工作线程
    class ThreadWorker {
    public:
        ThreadWorker(ThreadPool* pool_ptr, const int id) : pool_ptr_(pool_ptr), id_(id) {}

        void operator()() {
            std::function<void()> func;   
            bool get_success = false;  
            while (!pool_ptr_->task_queue_.empty() || !pool_ptr_->shutdown_) {
                {
                    // std::cout << "thread run, id: " << id_ << std::endl;
                    std::unique_lock<std::mutex> lock(pool_ptr_->conditional_mutex_);
                    // 如果任务为空 那么就要阻塞等待 
                    if (pool_ptr_->task_queue_.empty()) {
                        pool_ptr_->condition_lock_.wait(lock);     // 这里会释放lock ，重新恢复后 lock会重新加锁 
                    }
                    // 从任务队列中领取任务
                    get_success = pool_ptr_->task_queue_.pop(func);  
                }
                if (get_success) {
                    func();   // 执行任务  
                }
            }
        }

    private:
        int id_;
        ThreadPool* pool_ptr_;
    };

    bool shutdown_; 
    std::mutex conditional_mutex_; 
    std::condition_variable condition_lock_;  
    SafeQueue<std::function<void()>> task_queue_;
    // 工作线程队列
    std::vector<std::thread> threads_;
};