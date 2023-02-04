/*
 * @Copyright(C): 
 * @FileName: tuple.hpp
 * @Author: lwh
 * @Version: v1.0
 * @Date: 2021-11-24 12:27:49
 * @Description:  std::tuple的复现     
 * @Others:  主要学习 通过递归以及模板偏特化实现任意多参数的内存存储与读取  
 */

#pragma once 
#include "common.hpp"

namespace mySTL {

    // 原始版本的tuple 
    template<typename ... __args_type>
    class tuple {};

    // 无参的特化
    template<>
    class tuple<> {
        public:
            tuple() {}
            virtual ~tuple() {} 
    };

    //  带参偏特化
    template<typename __this_type, typename ...__args_type>
    class tuple<__this_type, __args_type...> : public tuple<__args_type ...> {
        public:
            tuple(__this_type val, __args_type ... params) : value_(val), 
                                                                                                            tuple<__args_type ...>(params ...) 
            {
            }

            virtual ~tuple() {}

            __this_type get_value() {
                return value_;  
            }

        private:
            __this_type value_;   
    }; // class tuple

    /**
     * @brief: element  原型模板类 
     * @details:  通过element获取tuple 指定位置的元素型别 
     * @param {*}
     * @return {*}
     */    
    template<int N, typename ... __args_type>
    struct element {};   

    // 偏特化   对于一个空的tuple 
    template<int N>
    struct element <N, tuple<>> {
        static_assert(0 > N, "Index outside of tuple!");
    }; 

    // 当N 不等于0 的偏特化   
    template<int N, typename __this_type, typename ... __args_type>
    struct element <N, tuple<__this_type, __args_type ...>> : public element<N - 1, tuple<__args_type ...>> {
        public:
            element() : element<N -1, tuple<__args_type ...>>() {}
    };

    // 当N = 0 时的偏特化
    template<typename __this_type, typename ... __args_type>
    struct element<0, tuple<__this_type, __args_type ...>>
    {
        using value_type = __this_type;    // 获取该元素的型别 
        using class_type = tuple<__this_type, __args_type...>;      // 获取对应tuple的对象 
    };

    /**
     * @brief: 获取tuple第N个元素的值
     * @details: 
     * @param N 要取的元素的模板序号 
     * @param tu tuple的引用  
     * @return 值
     */    
    template<size_t N, typename ... __args_type>
    auto get(tuple<__args_type ...> &tu) {
        // 先获取第N个元素对应tuple的型别
        using tuple_type =  typename element<N, tuple<__args_type ...>>::class_type;
        return static_cast<tuple_type&>(tu).get_value();  
    }
    

}; // namespace mySTL
