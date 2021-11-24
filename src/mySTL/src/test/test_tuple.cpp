/*
 * @Copyright(C): Your Company
 * @FileName: 
 * @Author: lwh
 * @Version: 版本
 * @Date: 2021-11-24 12:31:27
 * @Description: 
 * @Others: 
 */

#include "common.hpp"
 #include "tuple.hpp"
 
int main() {

    mySTL::tuple<int, float, std::string, char, std::string> tu{10, 4.5, "hehe", 'a', "yoyo"};

    std::cout<<"tuple 0: "<<mySTL::get<0>(tu)<<std::endl;
    std::cout<<"tuple 1: "<<mySTL::get<1>(tu)<<std::endl;
    std::cout<<"tuple 2: "<<mySTL::get<2>(tu)<<std::endl;
    std::cout<<"tuple 3: "<<mySTL::get<3>(tu)<<std::endl;
    std::cout<<"tuple 3: "<<mySTL::get<4>(tu)<<std::endl;

    return 0;  
}

