

#include <iostream>
#include <memory>
#include <boost/smart_ptr.hpp>
#include "shared_ptr.hpp"

using namespace std;
using namespace boost;  


int main()
{
    int *p = new int(10);
    my::shared_ptr<int> sp(p);  
    cout<<"shared_ptr point: "<<*sp<< endl;
    cout<<"use count(): "<<sp.use_count()<<endl;
    // 拷贝构造  
    my::shared_ptr<int> sp2 = sp;
    cout<<"use count(): "<<sp.use_count()<<endl;
    {
        my::shared_ptr<int> sp3 = sp2;
        cout<<"use count(): "<<sp3.use_count()<<endl;
    }
    cout<<"use count(): "<<sp2.use_count()<<endl;
    // 赋值操作
    my::shared_ptr<int> sp3;
    sp3 = sp;
    cout<<"use count(): "<<sp3.use_count()<<endl;
    return 0;  
}

