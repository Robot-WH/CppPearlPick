/*
 * @Copyright(C): Your Company
 * @FileName: 文件名
 * @Author: 作者
 * @Version: 版本
 * @Date: 2022-01-15 13:57:05
 * @Description: 
 * @Others: 
 */
#include <iostream>
#include <memory>
#include <boost/smart_ptr.hpp>
#include "scoped_ptr.hpp"
#include "make_scoped.hpp"

using namespace std;
using namespace boost;  


class test {
    public:
        test(const test&) {
            std::cout<<"test(const test&)"<<std::endl;
        }

        // test(test&& ) {
        //     std::cout<<"test(test&&)"<<std::endl;
        // }

        test(int t) {
            std::cout<<"test(int t)"<<std::endl;
        }
        
        const test& operator=(const test&) = delete;

}; 

int main()
{
    int *p = new int(10);
    // boost::scoped_ptr<int> sp(p);
    my::scoped_ptr<int> sp(p);  
    cout<<"p: "<<*sp<<endl;

    my::scoped_ptr<int> sp_1(new int(10));  
    // my::scoped_ptr<int> sp_3(sp);
    // sp_3 = sp;
    // reset
    int *p_2 = new int(100);
    sp.reset(p_2);
    cout<<"reset p: "<<*sp<<endl;

    // test T(10);  
    test T = 10;     // 先将10隐式转换为 test对象， 调用  test(int t) ， 然后，调用 拷贝构造函数  test(const test&)   
                                // 所以 若拷贝构造函数 被delete的话，test T = 10就无法 完成，编译器开启RVO优化后，会避免拷贝构造，
                                // 但是 如果拷贝构造函数 被delete的话，编译器还是会拒绝
    return 0;  
}

