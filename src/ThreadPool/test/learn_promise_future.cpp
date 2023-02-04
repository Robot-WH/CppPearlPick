
#include <iostream>
#include <future>

void task_1(int a, std::future<int>& b , std::promise<int>& ret) {
    int ret_a = a * a;
    int ret_b = b.get() * 2;    // 等待 b 所绑定的promise获取值   
    ret.set_value(ret_a + ret_b);
}

void task_2(int a, int b, std::promise<int>& ret) {
    int ret_a = a * a;
    int ret_b = b * 2;
    ret.set_value(ret_a + ret_b);
}

int main() {
    int ret = 0;

    std::promise<int> p_1;   // 保存int的promise
    std::future<int> f_1 = p_1.get_future();    // f_1绑定p_1   这样 f_1以后就能通过 get()拿到p_1的值了

    std::promise<int> p_2;   // 保存int的promise
    std::future<int> f_2 = p_2.get_future();    

    std::thread t_1(task_1, 1, std::ref(f_1), std::ref(p_2));
    std::thread t_2(task_2, 6, 6, std::ref(p_1));   // 对p_1 进行设置
    // get() 在 p值设置完成以前会保持阻塞  ，只能进行一次  
    std::cout << "return value is: " << f_2.get() << std::endl;   // 等待 p_2的值被设定

    t_1.join();
    t_2.join();     

    return 0;
}
