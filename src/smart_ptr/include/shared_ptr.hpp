#ifndef SHARED_PTR_HPP_
#define SHARED_PTR_HPP_

#include <iostream>
#include <memory>
#include <atomic>

using namespace std;  

namespace my {
    // 内存控制器基类
    class sp_counted_base {
        public:
            sp_counted_base() {
                cout<<"ceate sp_counted_base"<<endl;
            }

            virtual ~sp_counted_base() {
                cout<<"free sp_counted_base"<<endl;
            }

            void release() {
                // 判断是否需要真的析构  
                if(--count_use_==0) {
                       dispose();     // 延迟到子类实现 
                       delete this;  // 基类的析构函数设为virtual 这样 会递归的调用子类的析构  
                }
            }

            short use_count() const {
                return count_use_;
            }

            void add_ref_copy() {
                ++count_use_;  
            }

            virtual void dispose() = 0;   

        private: 
            // 不可移动，整个类失去了可移性 
            std::atomic<short> count_use_{1};     // atomic 不可用=初始化 ，不可用()
    }; // class sp_counted_base
    // 内存控制器子类
    // sp_counted_base 子类  保存了内存指针  ，已经实现了内存释放的接口 
    template<class _T>
    class sp_counted_impl_xx : public sp_counted_base {
        public:
            sp_counted_impl_xx(_T *p) : px_(p) {
                cout<<"ceate sp_counted_impl_xx"<<endl;
            }

            ~sp_counted_impl_xx() {
                cout<<"free sp_counted_impl_xx"<<endl;
            }

            void dispose() override {
                delete px_;   
            }
        private:
            _T *px_; 
    }; // class sp_counted_impl_xx
    // 内存控制器的封装层
    class shared_count {
        public:
            shared_count() 
                : pi_(nullptr) {
                cout<<"ceate shared_count"<<endl;
            }

            template<class _T>
            shared_count(_T *p) : pi_(new sp_counted_impl_xx<_T>(p)) {
                cout<<"ceate shared_count"<<endl;
            }
            // 拷贝构造
            shared_count(const shared_count &sc):pi_(sc.pi_) {
                if (pi_!=nullptr) {
                    pi_->add_ref_copy();  
                }
            }

            ~shared_count() {
                cout<<"free shared_count"<<endl;
                if(pi_ != nullptr) {
                    pi_->release();       // 调用基类的release   这里并不能直接delete  因为并不一定真的析构它，release只是使使用计数减一 
                }
            }

            short use_count() const {
                return pi_!=nullptr?pi_->use_count():0;
            }
            // 交换指向控制块的指针 pi_ 
            void swap(shared_count &sc)
            {
                sp_counted_base *tmp = sc.pi_;
                sc.pi_ = pi_;
                pi_ = tmp;  
            }
        private:
            sp_counted_base *pi_;     // 是否释放内存就是这个类管理的
    }; // class shared_count

    template<typename _T>
    class shared_ptr {
        public:
            shared_ptr() : p_(nullptr) {}
            shared_ptr(_T *p) : p_(p), pn_(p) {
                cout<<"ceate shared_ptr"<<endl;
            }
            ~shared_ptr() {
                cout<<"free shared_ptr"<<endl;
            }
            // 拷贝构造函数   核心！！！
            shared_ptr(const shared_ptr<_T>& ptr):p_(ptr.p_), pn_(ptr.pn_) {}
            // 赋值构造函数
            typedef shared_ptr<_T> this_type;
            shared_ptr<_T>& operator=(const shared_ptr<_T> &sp) {
                // 不是自己给自己赋值
                if (this != &sp) {
                    //  sp1 = sp2, 这里要求 sp2的计数器 ++ ， 而 sp1的计数器 --， 所以这里先通过  this_type(sp)  构造一个临时的
                    // 智能指针 使得sp2 的计数器++， 接着通过 swap 将当前智能指针的数据指针与控制器进行交换，接着利用临时智能指针
                    // 释放，使得sp1对应的计数器 -- 
                    this_type(sp).swap(*this);   // 先通过this_type() 调用拷贝构造，这样会使得use_count_++ ，接着交换p_
                }
                return *this;  
            }
            // @TODO  移动构造 ...
            
            _T const& operator*() {
                return *(get());  
            }

            _T* operator->() const {
                return get();
            }
            // get方法
            _T* get() const {
                return p_;  
            }
            // 获取该对象的指向次数   
            short use_count() const {
                return pn_.use_count();
            }
            void swap(shared_ptr<_T> &other) {
                std::swap(p_, other.p_);   
                pn_.swap(other.pn_);  
            }
        private:
            _T *p_;                                // 指向目标对象的指针, 这个指针只是为了使用，并不会进行内存的释放  
            shared_count pn_;       // 控制器   用来释放内存的 
    };  // class shared_ptr
};  // namespace my
#endif