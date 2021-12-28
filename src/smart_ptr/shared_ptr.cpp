/*
 * @Copyright(C): Your Company
 * @FileName: 文件名
 * @Author: 作者
 * @Version: 版本
 * @Date: 2021-11-14 16:27:05
 * @Description: 
 * @Others: 
 */


#include <iostream>
#include <memory>
#include <boost/smart_ptr.hpp>
#include "shared_ptr.hpp"
#include "make_shared.hpp"

using namespace std;
using namespace boost;  


int main()
{
    /* 下面是一个很不正确的做法，创建一个裸指针，再用多个shared_ptr去指向，这样会创建多个控制块，也就意味着多次的析构
    int *p = new int(10);
    my::shared_ptr<int> sp(p);  
    cout<<"shared_ptr point: "<<*sp<< endl;
    cout<<"use count(): "<<sp.use_count()<<endl;
    my::shared_ptr<int> sp2(p);  
    cout<<"shared_ptr point: "<<*sp2<< endl;
    cout<<"use count(): "<<sp2.use_count()<<endl;
    */
    // 正确的做法如下
    my::shared_ptr<int> sp( new int(10));  
    my::shared_ptr<int> sp1;
    sp1 = sp; 
    cout<<"shared_ptr point: "<<*sp1<< endl;
    cout<<"use count(): "<<sp1.use_count()<<endl;
    // 移动
    my::shared_ptr<int> sp2(std::move(sp1));
    cout<<"shared_ptr point: "<<*sp2<< endl;
    cout<<"use count(): "<<sp2.use_count()<<endl;
    // 移动自身
    sp2 = std::move(sp2);  
    cout<<"shared_ptr point: "<<*sp2<< endl;
    cout<<"use count(): "<<sp2.use_count()<<endl;

    return 0;  
}

