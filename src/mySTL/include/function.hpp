/*
 * @Copyright(C): Your Company
 * @FileName: 文件名
 * @Author: 作者
 * @Version: 版本
 * @Date: 2021-11-25 12:01:39
 * @Description: 
 * @Others: 
 */

#pragma once 

#include "common.hpp"
#include "bind.hpp"

namespace mySTL {

    /**
     * @brief:  BinderWrapper 基类  
     * @details:  在 function中只依赖这个基类 ， 对外的 函数为Call  设计为虚函数 供外界调用，BinderWrapperImpl 为它的子类 ，在 BinderWrapperImpl  中
     *                        完成对于binder 的保存以及Call的实现  
     * @param __return_type 函数返回型别
     * @param __args_type 函数参数型别 
     */    
    template<typename __return_type, typename ... __args_type>
    class BinderWrapperBase {
        public:
            virtual ~BinderWrapperBase() {}
            /**
             * @brief:  调用绑定的函数 
             * @details: 
             * @param __args_type 函数的输入参数类型
             * @return __return_type 注意 由于是 虚函数  所以这里不能用auto返回  ，所以采用模板
             */            
            virtual __return_type Call(__args_type ... args) = 0;  
    };  // class BinderWrapperBase

    template<typename __binder_type, typename __return_type, typename ... __args_type>
    class BinderWrapperImpl : public BinderWrapperBase<__return_type, __args_type ...> {
        public:
        
            BinderWrapperImpl(__binder_type binder) : binder_(binder) {}
            /**
             * @brief:  调用绑定的函数    重写   
             * @details:  调用 binder_ 实现  
             * @param __args_type 函数的输入参数类型
             * @return __return_type 模板参数  
             */            
            __return_type Call(__args_type ... args) override {
                return binder_(args ...);
            }

        private:
            __binder_type binder_;  
    }; // class BinderWrapperImpl

    /**
     * @brief:  std::function 实现  
     * @details: 
     * @param __Fx function 绑定的函数类型
     */    
    template<typename __return_type, typename ... __args_type>
    class function {
        public:
            // 构造    可以传入函数指针， 也可以i是bind的 返回  
            template<typename __binder_type>
            function(__binder_type binder) {
                binder_wrapper_ = new BinderWrapperImpl<__binder_type, __return_type, __args_type ...>{binder};  
            }
            // 析构函数  
            virtual ~function() {
                delete binder_wrapper_;   
            }
            // 仿函数  
            __return_type operator()(__args_type ... args) {
                return binder_wrapper_->Call(args ... ); 
            }

        private:
            BinderWrapperBase<__return_type, __args_type ...>  *binder_wrapper_ = nullptr;  
    }; // class function

    // 为了支持 类似与 void(int, int, string) 这种传参方式   ，下面进行偏特例化
    /**
     * @brief:  std::function 偏特例化
     * @details: 
     * @param __Fx function 绑定的函数类型
     */    
    template<typename __return_type, typename ... __args_type>
    class function<__return_type(__args_type ... )> {
        public:
            // 构造    可以传入函数指针， 也可以i是bind的 返回  
            template<typename __binder_type>
            function(__binder_type binder) {
                binder_wrapper_ = new BinderWrapperImpl<__binder_type, __return_type, __args_type ...>{binder};  
            }

            // 析构函数  
            virtual ~function() {
                delete binder_wrapper_;   
            }
            // 仿函数  
            __return_type operator()(__args_type ... args) {
                return binder_wrapper_->Call(args ... ); 
            }

        private:
            BinderWrapperBase<__return_type, __args_type ...>  *binder_wrapper_ = nullptr;  
    }; // class function

}; // class mySTL   
