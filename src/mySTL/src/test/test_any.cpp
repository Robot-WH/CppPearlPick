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

 template<class T>
 using Container = std::vector<T>;  

 template<class DataT, class T2 = int>
 class DataTest
 {
     public:
        DataTest()
        {
            datas.Registration<Container<DataT>>();  
        }
     private:
        mySTL::AnyVector datas;
 };
 
int main() {
    mySTL::Any a(std::string("hello"));
    std::cout<<"a: "<<a.Cast<std::string>()<<std::endl;
    a = 3.4;   // 先进行隐式类型转换
    std::cout<<"a: "<<a.Cast<double>()<<std::endl;

    mySTL::AnyVector aa;
    aa.Registration<float>(); 
    aa.AddData<float>(1.1);
    aa.AddData<float>(1.3);
    float d = 3;  
    aa.AddData(d);
    std::cout<<"getvalue: "<<aa.GetValue<float>(1)<<std::endl;
    std::cout<<"getvalue: "<<aa.GetValue<float>(2)<<std::endl;
    DataTest<int> dd;  
    std::vector<std::string> ct = {"hello"};
    aa.Registration<std::vector<std::string>>(); 
    // aa.AddData(ct);  
    // std::vector<std::string> v = aa.GetValue<std::vector<std::string>>(0); 
    // std::cout<<"v: "<<v[0]<<std::endl;
    return 0;  
}
