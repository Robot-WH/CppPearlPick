/*
 * @Copyright(C): Your Company
 * @FileName: 文件名
 * @Author: 作者
 * @Version: 版本
 * @Date: 2021-12-02 17:27:13
 * @Description: 
 * @Others: 
 */

#pragma once 

#include "common.hpp"

namespace mySTL {

    template <typename __T, __T v>
    struct integral_constant {
        static constexpr __T value = v;                                    ///  用value 保存值  
        using value_type = __T;
        using type = integral_constant<__T, v>;
        constexpr operator value_type() {return value;}    // ？？？？？？？？？？？？？？？？没看懂  ？？？？？？？？？？？
    }; 

    typedef integral_constant<bool, true> true_type;
    typedef integral_constant<bool, false> false_type;

}; // namespace mySTL   

