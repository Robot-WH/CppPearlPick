/*
 * @Copyright(C): Your Company
 * @FileName: 文件名
 * @Author: 作者
 * @Version: 版本
 * @Date: 2022-03-03 23:30:49
 * @Description: 
 * @Others: 
 */



#include "common.hpp"
 #include "container/vector/simple_vector.hpp"
#include "tic_toc.h"
#include <cmath>
#include <thread>

void test()
{
    while(1)
    {
        {
            int i = 1; 
            std::cout<<"haha"<<std::endl;
            if (i > 0) {
                std::this_thread::sleep_for(std::chrono::milliseconds(200));
                std::cout<<"haha 2"<<std::endl;
                continue;  
            }
        }
        
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
}

int main() {
   
    std::thread th(&test);
    th.join();
    return 0;  
}