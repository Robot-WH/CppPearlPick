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
#include "tuple.hpp"
#include "index_sequence.hpp"
#include "select_fixer.hpp"

namespace mySTL {

    /**
     * @brief: binder的作用是将函数与参数进行捆绑保存
     * @details 用于普通成员函数的保存 
     * @param Fx 函数指针的类型
     * @param __Args_type 参数类型  
     */    
    template<typename Fx, typename... __Args_type>
    class binder {
            public: 
                binder(Fx f, __Args_type... args) : m_f_(f),  args_(args...) {
                    std::cout<<"Fx construct"<<std::endl;
                }
                // // 仿函数
                // template<typename ... __args_type>
                // auto operator()(__args_type... args_in) {
                //     //std::cout<<"operator()(__args_type ... args)"<<std::endl;
                //     return Call(index_seq_, args_in...);
                // }

                // auto operator()() {
                //     //std::cout<<"operator()()"<<std::endl;
                //     return Call(index_seq_);  
                // }

                // template<size_t... __index, typename... __args_type>
                // auto Call(index_sequence<__index...>, __args_type... args_in) {
                //     return (*m_f_)(Select_fixer<decltype(get<__index>(args_))>::_Fix(get<__index>(args_),  args_in...)...);  
                //     //return (*m_f_)(param_wrapper<decltype(get<__index>(args_))>::get_value(get<__index>(args_), args_in...)...);  
                // }

                // 仿函数    需要调用类对象
                template<typename ... args_type>
                auto operator()(args_type ... args) {
                    return (*m_f_)(args ...);
                }

                // 重载    使用默认参数
                auto operator()() {
                    return Call(index_seq_);  
                }

                template<size_t... __index>
                auto Call(index_sequence<__index...>) {
                    return (*m_f_)(get<__index>(args_)...);      // 使用tuple 将函数参数输出
                }

            private:
                tuple<__Args_type...> args_;     // 通过tuple 保存 函数参数  
                make_index_sequence<sizeof...(__Args_type)> index_seq_;  // 生成模板序列  
                Fx m_f_;   
    }; // class binder

    /**
     * @brief: binder的作用是将函数与参数进行捆绑保存
     * @details 用于类内成员函数的保存
     * @param Fx 函数指针的类型
     * @param T 类的类型   
     * @param __Args_type 参数类型  
     */    
    template<typename Fx, typename T, typename... __Args_type>
    class mbinder {
        public:
            mbinder(Fx f, T *t, __Args_type... args) : m_f_(f), m_t_(t), args_(args...) {}

            // // 仿函数    需要调用类对象
            // template<typename ... args_type>
            // auto operator()(args_type ... args) {
            //     return Call(index_seq_, args ...);
            // }

            // // 重载    使用默认参数
            // auto operator()() {
            //     return Call(index_seq_);  
            // }

            // template<size_t... __index, typename... params>
            // auto Call(index_sequence<__index...>, params... args_in) {
            //     return (m_t_->*m_f_)(param_wrapper<decltype(get<__index>(args_))>::get_value(get<__index>(args_), args_in...)...);  
            // }

            // 仿函数    需要调用类对象
            template<typename ... args_type>
            auto operator()(args_type ... args) {
                return (m_t_->*m_f_)(args ...);
            }

            // 重载    使用默认参数
            auto operator()() {
                return Call(index_seq_);  
            }

            template<size_t... __index>
            auto Call(index_sequence<__index...>) {
                return (m_t_->*m_f_)(get<__index>(args_)...);  
            }

        private:
            Fx m_f_;    // 函数指针
            T *m_t_;     // 类对象指针 
            tuple<__Args_type...> args_;  
            make_index_sequence<sizeof...(__Args_type)> index_seq_;  
    };


    // bind函数的实现
    /**
     * @brief: bind的实现
     * @details:  对于普通函数重载  
     * @param Fx 绑定函数的型别 
     * @param __Args_type 绑定的参数类型
     * @return binder对象
     */    
    template<typename Fx, typename... __Args_type>
    auto bind(Fx f, __Args_type... args) {
        return binder<Fx, __Args_type...>(f, args...);   
    }

    /**
     * @brief: bind的实现
     * @details:  对于类成员函数重载  
     * @param Fx 绑定函数的型别 
     * @param __class_type 类的型别
     * @return f 函数指针 
     */    
    template<typename Fx, typename __class_type, typename... __Args_type>
    auto bind(Fx f, __class_type *c_o, __Args_type... args) {
        return mbinder<Fx, __class_type, __Args_type...>(f, c_o, args...);   
    }

};  // namespace mySTL