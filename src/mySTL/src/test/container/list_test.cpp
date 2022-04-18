/*
 * @Copyright(C): Your Company
 * @FileName: 文件名
 * @Author: 作者
 * @Version: 版本
 * @Date: 2022-01-16 17:43:13
 * @Description: 
 * @Others: 
 */
#include <stdio.h>
#include "common.hpp"
#include "container/list/list.hpp"
#include <memory>
#include <unordered_map>

template<typename _A>
class A
{
    public:
        template<typename _T>
        void Set(_T a)
        {
            // std::cout<<"v: "<<a<<std::endl;
        }

        void set()
        {

        }
};

template<typename _B>
class B
{
    public:
        _B v;  
};

template<typename _C>
class C
{
    public:
        void create()
        {
            std::unique_ptr<A<_C>> a_p(new A<_C>());
            //a->Set<B<_C>>(B<_C>());
            //a_p->Set<int>(1);  
            A<float> a;
            a.Set<int>(1); 
        }
};


template<typename _T>
void func()
{
    // std::unique_ptr<A<_T>> p{new A<_T>{}};
    // p->Set<int>(6);     // 这里报错 ，去掉int就可以运行  
    A<_T> p{};
    p.Set(6);     // 这里报错 ，去掉int就可以运行  
}

template <typename x>
struct cdr {
    using type = typename x::cdr_;
};

struct test
{
    std::shared_ptr<const int> p;  
    int c;
    std::unordered_map<std::string, std::shared_ptr<int>> m;  
};

// const 只能保证智能指针p指向的对象的地址不能变化 (也就是不能改变指向地址)， 但内容可以变化  
void get_test(test const& t)    
{
    std::shared_ptr<const int> p;
    p.reset(new int(20));
    //t.p = p;    // const shared_ptr 不能改变指针的指向 
    p = t.p;  // p 没发生变化   所以可以
    // *p = 20;
    //*t.p = 10;    // const  无效
    //t.p.reset(new int(20));   // const 禁止  
    // t.p = p;  // const 禁止
    // int i = *t.m["h"];     // 不能用[]  , [] 会在key不存在时自动创建  所以   与const 冲突 
    int i = *t.m.find("h")->second; 
}


    template<class T>
    inline T AlignValue(size_t value, size_t alignValue = 8) {
      return static_cast<T> ((value + (alignValue - 1)) & ~(alignValue - 1));
    }

    template<class T>
    inline T AlignValue2(size_t value, size_t alignValue = 8) {
        if (value % alignValue)
            value = (value / alignValue + 1) * alignValue;
      return static_cast<T> (value);
    }

    void test_pp(int k)
    {
        std::cout<<"k: "<<k<<std::endl;
    }



int main() 
{
    // func<int>(); 
    // // std::unique_ptr<A<int>> p(new A<int>());
    // // p->Set<double>(6);     // 这里报错 ，去掉int就可以运行  
    // test t;
    // t.p.reset(new int(10));
    // t.p.reset(new int(1));
    
    // std::cout<<"t.p: "<<*t.p<<std::endl;
    // t.m.insert(std::make_pair("h", new int(10)));
    // get_test(t);

    // std::cout<<"AlignValue: "<<AlignValue<int>(17,6)<<std::endl;
    // std::cout<<"AlignValue2: "<<AlignValue2<int>(17,6)<<std::endl;

    // float k = 0.000012;
    // A<int> aa;
    // aa.Set<float>(1.0);
    // aa.Set<std::string>("hello");

    // C<float> cc;
    int k = 0;
    test_pp(k++);
    std::cout<<"k: "<<k<<std::endl;
    return 0;  
}