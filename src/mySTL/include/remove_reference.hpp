/*
 * @Copyright(C): Your Company
 * @FileName: 文件名
 * @Author: 作者
 * @Version: 版本
 * @Date: 2021-11-23 17:14:36
 * @Description: 
 * @Others: 
 */

#pragma once 
#include <iostream>

namespace mySTL {

    template<typename T>
    struct remove_reference {
        public:
            typedef T type;  
    };   

    // 对左值引用的特化
    template<typename T>
    struct remove_reference<T&> {
        public:
            typedef T type;  
    };   

    // 对右值引用的特化
    template<typename T>
    struct remove_reference<T&&> {
        public:
            typedef T type;  
    };   

    template<class T>
    using remove_reference_t = typename remove_reference<T>::type;  

};  // namespace mySTL
