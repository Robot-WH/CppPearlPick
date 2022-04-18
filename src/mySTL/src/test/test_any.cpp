/*
 * @Copyright(C): Your Company
 * @FileName: 文件名
 * @Author: 作者
 * @Version: 版本
 * @Date: 2022-04-18 17:56:46
 * @Description: 
 * @Others: 
 */
#include "common.hpp"
 #include "any.hpp"
 #include "any_vector.hpp"
 
int main() {
    mySTL::Any a(std::string("hello"));
    std::cout<<"a: "<<a.Cast<std::string>()<<std::endl;
    a = 3.4;   // 先进行隐式类型转换
    std::cout<<"a: "<<a.Cast<double>()<<std::endl;

    mySTL::AnyVector aa;
    aa.Registration<float>(); 
    aa.AddData<float>(1.1);
    aa.AddData<float>(1.3);
    aa.AddData<float>(3);
    std::cout<<"getvalue: "<<aa.GetValue<float>(1)<<std::endl;
    std::cout<<"getvalue: "<<aa.GetValue<float>(2)<<std::endl;

    return 0;  
}
