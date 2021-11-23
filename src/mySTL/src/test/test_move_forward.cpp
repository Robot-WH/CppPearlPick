/*
 * @Copyright(C): Your Company
 * @FileName: 文件名
 * @Author: 作者
 * @Version: 版本
 * @Date: 2021-11-23 18:15:33
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

  int a = 10;   // 左值
  int &b = a;  // 左值引用  
  int &&c = 10;  

  print_is_same<decltype(mySTL::move(a)), int &&>();    // 左值转右值引用
  print_is_same<decltype(mySTL::move(b)), int &&>();    
  print_is_same<decltype(mySTL::move(c)), int &&>();

  // move 对 const的 作用
  const int d = 10;  
  print_is_same<decltype(mySTL::move(d)), const int &&>();   // move 后变成  const int && 

}

