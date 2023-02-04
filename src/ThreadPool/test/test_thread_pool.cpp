
#include <iostream>
#include <random>
#include "../thread_pool.hpp"
#include "../multi_thread_pool.hpp"
std::random_device rd; 
std::mt19937 mt(rd());
std::uniform_int_distribution<int> dist(-1000, 1000);   // 生成 -1000, 1000的随机分布
auto rnd = std::bind(dist, mt);

// 设置线程睡眠时间 
void simulate_hard_computation() {
    std::this_thread::sleep_for(std::chrono::milliseconds(2000 + rnd()));
}

void multiply(const int a, const int b) {
    simulate_hard_computation();
    const int res = a * b;
    std::cout << a << " * " << b << " = " << res << std::endl;
}

void multiply_output(int& out, const int a, const int b) {
    simulate_hard_computation();
    out = a * b;
}

int multiply_return(const int a, const int b) {
    simulate_hard_computation();
    int res = a * b;
    return res; 
}

int main() {
    std::cout << "----------------------test ThreadPool ---------------------------" << std::endl;
    ThreadPool thread_pool(4);
    // 创建30个乘法任务
    for (int i = 0; i <= 3; ++i) {
        for (int j = 0; j <= 3; ++j) {
            thread_pool.submit(multiply, i, j);
        }
    }
    std::cout << "30 multiply task create finish" << std::endl;

    int output_ref; 
    auto future1 = thread_pool.submit(multiply_output, std::ref(output_ref), 5, 6);

    future1.get();  // 等待上面任务完成  
    std::cout << "last operation is equals to: " << output_ref << std::endl;

    auto future2 = thread_pool.submit(multiply_return, 7, 6);
    int res = future2.get();
    std::cout << "last operation is equals to: " << res << std::endl;

    thread_pool.shutdown();  

    std::cout << "----------------------test MultipleThreadPool ---------------------------" << std::endl;

    MultipleThreadPool mt_pool;  

    // 创建30个乘法任务
    for (int i = 1; i <= 2; ++i) {
        for (int j = 1; j <= 5; ++j) {
            mt_pool.submit(multiply, i, j);
        }
    }
    std::cout << "10 multiply task create finish" << std::endl;

    auto future3 = mt_pool.submit(multiply_output, std::ref(output_ref), 5, 6);

    future3.get();  // 等待上面任务完成  
    std::cout << "last operation is equals to: " << output_ref << std::endl;

    auto future4 = mt_pool.submit(multiply_return, 7, 6);
    res = future4.get();
    std::cout << "last operation is equals to: " << res << std::endl;

    return 0;
}