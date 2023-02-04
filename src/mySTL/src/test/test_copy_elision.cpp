
#include "common.hpp"

    class Foo { 
    public:
        Foo() { std::cout<<"default"<<std::endl; }
        Foo(int i) : i_(i) { std::cout<<"i:" << i_<<std::endl; }

        // Foo(const Foo& rhs) { std::cout<<"ctor"<<std::endl; }
        Foo(Foo&& rhs) { std::cout<<"mtor"<<std::endl; }
        // 移动/拷贝构造被delete都会影响移动/拷贝构造函数的自动生成，因此一定要手动定义其他的移动/拷贝构造
        Foo(const Foo& rhs) = delete;   
        // Foo(Foo&& rhs) = delete;  
    private:
      int i_ = 0; 
    };

    Foo return_urvo_value() { 
      return Foo{};    // 若没开启URVO优化，则调用两次移动构造函数
    }

    Foo return_nrvo_value() { 
      Foo local_obj(10);
      return local_obj; // 若没开启NRVO优化，则调用两次移动构造函数 
    }


int main() {
    auto x = return_urvo_value();
    std::cout<<"---------------------------------------"<<std::endl;
    auto y = return_nrvo_value();  
    return 0;
}