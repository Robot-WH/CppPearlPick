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
     * @brief: 
     * @details: 
     * @param {*}
     */    
    template<typename __Cv_TiD, int __Fx = is_placeholder_v<__Cv_TiD>>
    struct  Select_fixer {

        template<typename... __Args>
        static constexpr auto _Fix(__Cv_TiD& _Tid, __Args... args) {
            //static_cast(__Fx > 0, "invalid is_placeholder value");
            tuple<__Args...> tu{args...};   
            return get<__Fx - 1>(tu);      // 无引用  无const      仅仅是把值取出来  
        }
    };
    
    /**
     * @brief: __Cv_TiD 是一个普通类型 (非占位符)
     * @details: 
     * @param {*}
     */    
    template<typename __Cv_TiD>
    struct  Select_fixer<__Cv_TiD, 0> {
        template<typename... __Args>
        static constexpr __Cv_TiD& _Fix(__Cv_TiD const& _Tid, __Args... args) {
            return _Tid;
        }
    };


    /////////////////////////////////////////////////////////////////////////另一种尝试 ////////////////////////////////////////////////////////////////////////
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
     * @brief:  偏特化  
     * @details: 
     * @param {*}
     * @return {*}
     */    
    template<size_t _index>   
    class param_wrapper<_placeholders_<_index>>  {   
        public:    
        // 对于占位符 采用下面方式对参数进行取值
        template<typename... Args> 
        static auto get_value(_placeholders_<_index> val, Args... args) { 
            tuple<Args...> tu{args...};   
            return get<_index - 1>(tu);   
        }  
    }; 


};  