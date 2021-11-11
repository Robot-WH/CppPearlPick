
#ifndef SHARED_PTR_HPP_
#define SHARED_PTR_HPP_

#include <iostream>
#include <memory>
using namespace std;  

namespace my {

    class sp_counted_base
    {
        public:
            sp_counted_base()
            {
                cout<<"ceate sp_counted_base"<<endl;
            }

            ~sp_counted_base()
            {
                cout<<"free sp_counted_base"<<endl;
            }

        private:
            short use_count_;   

    };

    template<class _T>
    class sp_counted_impl_xx : public sp_counted_base
    {
        public:
            sp_counted_impl_xx(_T *p) : px_(p)
            {
                cout<<"ceate sp_counted_impl_xx"<<endl;
            }

            ~sp_counted_impl_xx()
            {
                cout<<"free sp_counted_impl_xx"<<endl;
            }
        private:
            _T *px_; 
    };

    class shared_count
    {
        public:
            shared_count()
            {
                cout<<"ceate shared_count"<<endl;
            }

            template<class _T>
            shared_count(_T *p) : pi_(new sp_counted_impl_xx<_T>(p))
            {
                cout<<"ceate shared_count"<<endl;
            }

            ~shared_count()
            {
                cout<<"free shared_count"<<endl;
            }
        private:
            sp_counted_base* pi_;  

    };

    template<typename _T>
    class shared_ptr
    {
        public:
            shared_ptr(_T *p) : p_(p), pn_(p)
            {

                cout<<"ceate shared_ptr"<<endl;
            }
            ~shared_ptr()
            {

                cout<<"free shared_ptr"<<endl;
            }
        private:
            _T *p_;
            shared_count pn_;   
    };


    
};  // namespace my

#endif