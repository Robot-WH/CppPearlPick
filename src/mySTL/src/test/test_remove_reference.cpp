/*
 * @Copyright(C): Your Company
 * @FileName: 文件名
 * @Author: 作者
 * @Version: 版本
 * @Date: 2021-11-23 17:03:49
 * @Description: 
 * @Others: 
 */

#include <iostream> // std::cout
#include <type_traits> // std::is_same
#include "common.hpp"
 
template<class T1, class T2>
void print_is_same() {
  std::cout << std::is_same<T1, T2>() << '\n';
}
 
int main() {
  std::cout << std::boolalpha;
 
  print_is_same<int, int>();
  print_is_same<int, int &>();
  print_is_same<int, int &&>();
 
  print_is_same<int, std::remove_reference<int>::type>();
  print_is_same<int, std::remove_reference<int &>::type>();
  print_is_same<int, std::remove_reference<int &&>::type>();

  print_is_same<int, mySTL::remove_reference<int>::type>();
  print_is_same<int, mySTL::remove_reference<int &>::type>();
  print_is_same<int, mySTL::remove_reference<int &&>::type>();
  print_is_same<int, mySTL::remove_reference<int &&>::type>();

  print_is_same<int, mySTL::remove_reference_t<int>>();
  print_is_same<int, mySTL::remove_reference_t<int &>>();
  print_is_same<int, mySTL::remove_reference_t<int &&>>();
  
}
