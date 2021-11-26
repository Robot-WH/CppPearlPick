/*
 * @Copyright(C): Your Company
 * @FileName: 文件名
 * @Author: 作者
 * @Version: 版本
 * @Date: 2021-11-26 19:12:53
 * @Description: 
 * @Others: 
 */

#pragma once 
#include "common.hpp"

namespace mySTL {

    /**
     * @brief 通过模板参数__INDEX保存序列的类  
     * @param __INDEX 序列
     */    
    template<size_t... __INDEX>
    class index_sequence {};
    /**
     * @brief: 通过迭代生成从 N , N -1, ........ 0的序列
     * @details: 
     * @param _N 序列的起始量
     * @param __INDEX 序列  
     */    
    template<size_t _N, size_t... __INDEX>
    class make_index_sequence : public make_index_sequence<_N - 1, _N - 1, __INDEX...> {};  

    template<size_t... __INDEX>
    class make_index_sequence<0, __INDEX...> : public index_sequence<__INDEX...> {};  

};   // namespace mySTL

