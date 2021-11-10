
#include <iostream>
#include <memory>
#include <boost/smart_ptr.hpp>

using namespace std;
using namespace boost;  

namespace my {

    template<typename _T>
    class scoped_ptr
    {
        public:
            scoped_ptr(_T *p = nullptr) : p_(p)
            {}
            ~scoped_ptr()
            {
                delete p_;  
            }
            // *操作符重载
            _T& operator*()
            {
                return *p_;  
            }
            // -> 重载  直接返回指针
            _T* operator->()    
            {
                return p_;  
            }
        
            scoped_ptr(const scoped_ptr<_T>&) = delete;
            const scoped_ptr<_T>& operator=(const scoped_ptr<_T>&) = delete;
            void operator==(const scoped_ptr<_T>&)  const = delete;
            void operator!=(const scoped_ptr<_T>&)  const = delete;

            typedef scoped_ptr<_T> this_type;  

            void reset(_T *p = nullptr)
            {
                this_type(p).swap(*this);
            }

        protected:
            // 交换指针
            void swap(scoped_ptr& sp)
            {
                _T *tmp = sp.p_;
                sp.p_ = p_;
                p_ = tmp;   
            }

        private:
            _T *p_;
    }; // class  scoped_ptr
};  

int main()
{
    int *p = new int(10);
    // boost::scoped_ptr<int> sp(p);
    my::scoped_ptr<int> sp(p);  
    cout<<"p: "<<*sp<<endl;
    string *s = new string("hello");
    my::scoped_ptr<string> sp_2(s);
    cout<<"s size: "<<sp_2->size()<<endl;
    // my::scoped_ptr<int> sp_3(sp);
    // sp_3 = sp;
    // reset
    int *p_2 = new int(100);
    sp.reset(p_2);
    cout<<"reset p: "<<*sp<<endl;
    return 0;  
}

