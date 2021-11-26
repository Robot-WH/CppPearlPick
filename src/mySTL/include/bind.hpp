/*
 * @Copyright(C): Your Company
 * @FileName: 文件名
 * @Author: 作者
 * @Version: 版本
 * @Date: 2021-11-24 19:42:05
 * @Description: 
 * @Others: 
 */
#pragma once 

#include "common.hpp"

namespace mySTL {

    template<typename Fx>
    class binder {
            public: 
                explicit binder(Fx f) : m_f_(f) {
                    std::cout<<"Fx construct"<<std::endl;
                }

                template<typename ... __args_type>
                auto operator()(__args_type ... args) {
                        return (*m_f_)(args ...);
                }

            private:
                Fx m_f_;   

    }; // class binder

    /**
     * @brief: 
     * @details: 
     * @param Fx 函数指针的类型
     * @param T 类的类型   
     * @return {*}
     */    
    template<typename Fx, typename T>
    class mbinder {
        public:
            mbinder(Fx f, T *t) : m_f_(f), m_t_(t) {}

            // 仿函数    需要调用类对象
            template<typename ... args_type>
            auto operator()(args_type ... args) {
                return (m_t_->*m_f_)(args ...);
            }

        private:
            Fx m_f_;    // 函数指针
            T *m_t_;     // 类对象指针 
    };


    // bind函数的实现
    /**
     * @brief: bind的实现
     * @details:  对于普通函数重载  
     * @param Fx 绑定函数的型别 
     * @return f 函数指针
     */    
    template<typename Fx>
    auto bind(Fx f) {
        return binder<Fx>(f);   
    }

    /**
     * @brief: bind的实现
     * @details:  对于类成员函数重载  
     * @param Fx 绑定函数的型别 
     * @param __class_type 类的型别
     * @return f 函数指针 
     */    
    template<typename Fx, typename __class_type>
    auto bind(Fx f, __class_type *c_o) {
        return mbinder<Fx, __class_type>(f, c_o);   
    }

};  // namespace mySTL