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

    template<uint16_t _Nx>
    struct  _placeholders_ {
        static_assert(_Nx > 0, "invalid placeholder index");
    };

    #define _placeholders_(i) _placeholders_<i>{}

    namespace placeholders {
        // 定义若干个_placeholders_ 对象
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
    struct is_placeholder : integral_constant<int, 0> {

        is_placeholder() {
            std::cout<<" un placeholders_ _Nx: "<<0<<std::endl;
        }
        static constexpr bool is_placeholder_ = false;     // 不是placeholder的标志位  
    };   

    /**
     * @brief:  _Tx 为 _placeholders_ 时的特化  
     * @details: integral_constant 保存 _Nx 参数   
     * @param {*}
     * @return {*}
     */
    template<uint16_t _Nx>
    struct is_placeholder<_placeholders_<_Nx>> : integral_constant<uint16_t, _Nx> {
        is_placeholder() {
            std::cout<<"_placeholders_ _Nx: "<<_Nx<<std::endl;
        }
        
        static constexpr bool is_placeholder_ = true;   
    };   
    // 如果是placeholder 则获取占位值 
    // 下面是 变量模板  - C++  14引入  
    template<typename _Ty>
    constexpr uint16_t is_placeholder_v = is_placeholder<_Ty>::value; // constexpr 要求编译期已知，并可以设置模板参数   
    // 获取是否是placeholder  
    template<typename _Ty>
    constexpr bool is_placeholder_b = is_placeholder<_Ty>::is_placeholder_;  

    // 模板原型  
    template<typename __Cv_TiD, bool = is_placeholder_b<__Cv_TiD>,  uint16_t  = is_placeholder_v<__Cv_TiD>>
    struct  Select_fixer {}; 

    /**
     * @brief: placeholder 值获取 
     * @details: 
     * @param {*}
     */    
    template<typename __Cv_TiD, uint16_t __Fx>
    struct  Select_fixer<__Cv_TiD, true, __Fx> {

        Select_fixer() {
            std::cout<<"Select_fixer placeholder construct, __Fx: "<<__Fx<<std::endl;
        }

        template<typename... __Args>
        static constexpr auto _Fix(__Cv_TiD const& _Tid, __Args... args) {
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
    struct  Select_fixer<__Cv_TiD, false, 0> {
        Select_fixer() {
            std::cout<<"Select_fixer un-placeholder construct"<<std::endl;
        }

        template<typename... __Args>
        static constexpr __Cv_TiD _Fix(__Cv_TiD const& _Tid, __Args... args) {
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
            param_wrapper() {
                std::cout<<"param_wrapper __placeType"<<std::endl;
            }
            template<typename... Args>
            static constexpr auto get_value(__placeType val, Args... args) {
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
        param_wrapper() {
            std::cout<<"param_wrapper _placeholders_, _index: "<<_index<<std::endl;
        }
        // 对于占位符 采用下面方式对参数进行取值
        template<typename... Args> 
        static constexpr auto get_value(_placeholders_<_index> val, Args... args) { 
            tuple<Args...> tu{args...};   
            return get<_index - 1>(tu);   
        }  
    }; 


};  