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
   * @details:  
   * @param param  万能引用    输入
   * @return remove_reference_t<T>&& 右值引用   
   */  
  template<typename T>
  decltype(auto) move(T&& param) {
      using ReturnType = remove_reference_t<T>&&;    // 构造出右值引用
      return static_cast<ReturnType>(param);            // 强制转换 
  }

  


}; //  namespace mySTL  


