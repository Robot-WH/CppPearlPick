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

namespace mySTL {


    template<typename __placeType>
    class  param_wrapper {
        public:
        	template<typename... Args>
            static auto get_value(placeType val, Args... args) {
                return val;   // 对于普通类型  直接返回元素值
            }

    };

    template<size_t _Nx>
    struct  _placeholders_ {
        static_assert(_Nx > 0, "invalid placeholder index");
    };
    #define _placeholders_(i) _placeholders_<i>{}


    namespace placeholders {
            using _1 = _placeholders_<1>();
            using _2 = _placeholders_<2>();  
            using _3 = _placeholders_<3>();  
            using _4 = _placeholders_<4>();  
            using _5 = _placeholders_<5>();  
            using _6 = _placeholders_<6>();  
            using _7 = _placeholders_<7>();  
            using _8 = _placeholders_<8>();  
            using _9 = _placeholders_<9>();  
    };
    

    // 对param_wrapper 类的全特化
    #define place_param_wrapper(index) \
                    template<>   \    
                    class param_wrapper<_placeholders_<index>>  {   \
                        public:     \
                        template<typename... Args>  \
                        static auto get_value(_placeholders_<index> &val, Args... args) { \
                            tuple<Args...> tu{args...};   \
                            return get<index - 1>(tu);   \
                        }  \
                    }; \
                      
    place_param_wrapper(1);
    place_param_wrapper(2);
    place_param_wrapper(3);
    place_param_wrapper(4);
    place_param_wrapper(5);
    place_param_wrapper(6);
    place_param_wrapper(7);
    place_param_wrapper(8);
    place_param_wrapper(9);

};  