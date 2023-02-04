/*
 * @Copyright(C): 
 * @FileName: common.hpp
 * @Author: lwh
 * @Version: v1.0
 * @Date: 2021-11-19 17:23:10
 * @Description:  stl 通用
 * @Others: 
 */

#pragma once 
#include <iostream>
#include "remove_reference.hpp"

namespace mySTL {

  /**
   * @brief:  std::move 的复现
   * @details:  任何变量强制转换为右值引用
   * @param param  万能引用    输入
   * @return remove_reference_t<T>&& 右值引用   
   */  
  template<typename T>
  decltype(auto) move(T&& param) {
      using ReturnType = remove_reference_t<T>&&;    // 构造出右值引用
      return static_cast<ReturnType>(param);            // 强制转换 
  }

  /**
   * @brief: std::forward的复现，用法是  forward<T>(param)
   * @details: 有条件的执行强制转换为右值引用
   * @param T  通过上级函数 万能引用推导出来的，要么 左值，要么左值引用
   * @param param 左值引用，只能输入左值或左值引用
   * @return param T为左值则return 右值引用 ， T为左值引用 则return 左值引用
   */  
  template<typename T>
  T&& forward(remove_reference_t<T>& param) {
      return static_cast<T&&>(param);
  }
  
}; //  namespace mySTL  


