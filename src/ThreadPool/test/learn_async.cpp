
#include <iostream>
#include <future>
#include <functional>

int task_1(int a, int b) {
    int ret_a = a * a;
    int ret_b = b * 2;    // 等待 b 所绑定的promise获取值   
    return ret_a + ret_b;
}

int main() {
    int ret = 0;

    std::future<int> fu = std::async(task_1, 1, 2); // 默认std::launch::deferred 
    // std::future<int> fu = std::async(std::launch::async, task_1, 1, 2);  // 会创建一个新的线程
    // std::future<int> fu = std::async(std::launch::deferred, task_1, 1, 2);   // 延迟调用  ，不会创建线程 
    std::cout << "return value is: " << fu.get() << std::endl;  // 这里会阻塞  直到 async结束并有返回值  
    std::packaged_task<int(int, int)> t(task_1);    // packaged_task 可以获取 future  
    t(1, 4);
    std::cout << "return value is:" << t.get_future().get() << std::endl;
    std::packaged_task<int()> t_2(std::bind(task_1, 1, 3));    // packaged_task 可以获取 future  
    t_2();
    std::cout << "return value is:" << t_2.get_future().get() << std::endl;

    return 0;
}
