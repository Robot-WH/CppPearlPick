/*
 * @Copyright(C): Your Company
 * @FileName: 文件名
 * @Author: 作者
 * @Version: 版本
 * @Date: 2021-12-02 12:48:34
 * @Description: 
 * @Others: 
 */

#pragma once 

#include "common.hpp"
#include "tuple.hpp"
#include "integral_constant.hpp"

namespace mySTL {


    template<size_t _Nx>
    struct  _placeholders_ {
        static_assert(_Nx > 0, "invalid placeholder index");
    };
    #define _placeholders_(i) _placeholders_<i>{}

    namespace placeholders {
        constexpr _placeholders_<1> _1{};
        constexpr _placeholders_<2> _2{};
        constexpr _placeholders_<3> _3{};
        constexpr _placeholders_<4> _4{};
        constexpr _placeholders_<5> _5{};
        constexpr _placeholders_<6> _6{};
        constexpr _placeholders_<7> _7{};
        constexpr _placeholders_<8> _8{};
        constexpr _placeholders_<9> _9{};
    };

/**
 * @brief:  用于判定是否为 placeholder 的类原型   
 * @details: 
 * @param {*}
 * @return {*}
 */    
template<typename _Tx>
struct is_placeholder : integral_constant<int, 0> {};   

/**
 * @brief:  _Tx 为 _placeholders_ 时的特化  
 * @details: integral_constant 保存 _Nx 参数   
 * @param {*}
 * @return {*}
 */
template<int _Nx>
struct is_placeholder<_placeholders_<_Nx>> : integral_constant<int, _Nx> {};   


template<typename _Ty>
constexpr int is_placeholder_v = is_placeholder<_Ty>::value;  



    /**
     * @brief:  参数包装器  原型
     * @details:  
     * @param {*}
     * @return {*}
     */    
    template<typename __placeType>
    class  param_wrapper {
        public:
        	template<typename... Args>
            static auto get_value(__placeType val, Args... args) {
                return val;   // 对于普通类型  直接返回元素值
            }
    };

    /**
     * @brief:  特化  
     * @details: 
     * @param {*}
     * @return {*}
     */    
    template<size_t _index>   
    class param_wrapper<_placeholders_<_index>>  {   
        public:    
        template<typename... Args> 
        static auto get_value(_placeholders_<_index> val, Args... args) { 
            tuple<Args...> tu{args...};   
            return get<_index - 1>(tu);   
        }  
    }; 


};  