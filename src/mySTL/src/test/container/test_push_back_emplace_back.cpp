/*
 * @Copyright(C): Your Company
 * @FileName: 文件名
 * @Author: 作者
 * @Version: 版本
 * @Date: 2022-09-24 15:31:13
 * @Description: 
 * @Others: 
 */

#include<ostream>
#include <iostream>
#include <vector>
#include <deque>
#include <stdio.h>
#include<cstring>
#include "common.hpp"
#include "container/list/list.hpp"
#include <memory>
#include <unordered_map>
#include<iomanip>
#include <chrono>
#include <eigen3/Eigen/Dense>

using namespace mySTL;
using namespace std;
using namespace chrono;

class A {
public:
  A (int x_arg) : x (x_arg) { 
      std::cout << "A (x_arg)\n"; 
  }
  A () { 
    x = 0; 
    std::cout << "A ()\n"; 
    }

  A (const A &rhs)  { 
    x = rhs.x; 
    ss = rhs.ss;  
    std::cout << "A (A &)\n"; 
  }

    A (A &&rhs) noexcept : x(rhs.x), ss(std::move(rhs.ss))  { 
    //   x = rhs.x; 
    //   ss = std::move(rhs.ss);  
      std::cout << "A (A &&)\n"; 
    }

    A& operator=(const A &a) {
      std::cout<<"拷贝赋值"<<std::endl;
      x = a.x;  
      ss = a.ss; 
      return *this; 
    }

    A& operator=(A&&a) {
      std::cout<<"移动赋值"<<std::endl;
      x = a.x;  
      ss = std::move(a.ss);
      return *this;  
    }

    // 自定义了析构   不会自己生成默认移动构造  
  ~A() { 
      std::cout << "~A ()\n"; 
    }

public:
  int x = 0;
  string ss = string(100, 'a');
};

void test_emplace_back_1()
{
	// For emplace_back constructor A (int x_arg) will be called.
	// And for push_back A (int x_arg) is called first and 
	// move A (A &&rhs) is called afterwards
  {
    std::vector<A> a;
    std::cout << "call emplace_back_1:\n";
    a.emplace_back(0); 
	// (1) direct object creation inside vector
  }

  {
    std::vector<A> a;
    std::cout << "call push_back1:\n";
    a.push_back(1);
	// (1) create temp object and 
	// (2) then move copy to vector and 
	// (3) free temp object
  }
}

void test_emplace_back_2()
{
	// emplace_back and push_back for `A(0)`, it's same.
	// A (int x_arg) is called first and 
	// move A (A &&rhs) is called afterwards
  {
    std::vector<A> a;
    std::cout << "call emplace_back_2:\n";
    a.emplace_back(A(0)); 
	// (1) create temp object and 
	// (2) then move copy to vector and 
	// (3) free temp object
  }

  {
    std::vector<A> a;
    std::cout << "call push_back2:\n";
    a.push_back(A(1));
	// (1) create temp object and 
	// (2) then move copy to vector and 
	// (3) free temp object
  }
}

void test_emplace_back_3()
{
	// emplace_back and push_back for `A obj(0)`, it's same.
	// A (int x_arg) is called first and 
	// copy constructor A (A &) is called afterwards
  {
    std::vector<A> a;
    std::cout << "call emplace_back3:\n";
    A obj(0);
    a.emplace_back(obj); 
	 // copy constructor to vector
  }
  std::vector<A> a;
  std::cout << "call push_back3:\n";
  auto start = system_clock::now();
  for (int i = 0; i < 300000; i++)
  {
    A obj(1);
    a.push_back(obj);
	 // copy constructor to vector
  }
    auto end = system_clock::now();
    auto duration = duration_cast<milliseconds>(end - start);
    cout << "time duration ms: " << duration.count() << endl; 
}

void test_emplace_back_4()
{
	// emplace_back and push_back for `A obj(0)`, it's same.
	// A (int x_arg) is called first and 
	// copy constructor A (A &) is called afterwards
  {
    std::vector<A> a;
    std::cout << "call emplace_back4:\n";
    A obj(0);
    a.push_back(std::move(obj)); 
	 // copy constructor to vector
  }
  
    // std::vector<A> a;
    // std::cout << "call push_back4:\n";
    // auto start = system_clock::now();
    // for (int i = 0; i < 300000; i++)
    // {
    //     A obj(1);
    //     a.push_back(std::move(obj));
    //     // copy constructor to vector
    // }
    //     auto end = system_clock::now();
    //     auto duration = duration_cast<milliseconds>(end - start);
    //     cout << "time duration ms: " << duration.count() << endl; 
}

enum class Type {
    A = 0,
    B,
    C
};

int main() 
{
  //  test_emplace_back_1();
  //  test_emplace_back_2();
  //   test_emplace_back_3(); 
    test_emplace_back_4();
    // std::deque<A> A_C; 
    // A_C.resize(10);
    // A a{100};
    // std::cout<<"x:" <<a.x<<std::endl;
    // a = std::move(A_C.front()); 
    // std::cout<<"x:" <<a.x<<std::endl;
    std::deque<int> dq;
    dq.push_back(10);
    dq.push_back(18);
    int& n = dq.front();  
    auto iter = dq.begin();  
    std::cout << "n:" << n << std::endl;
    std::cout << "iter:" << *iter << std::endl;
    for (int i = 0; i < 1000; ++i) 
      dq.push_back(18);
    std::cout << "n:" << n << std::endl;   // 往后添加元素后，引用和迭代依然有效
    std::cout << "iter:" << *iter << std::endl;
    for (int i = 0; i < 1000; ++i) 
      dq.push_front(18);
    std::cout << "n:" << n << std::endl;   // 往前添加元素后，引用和迭代依然有效
    std::cout << "iter:" << *iter << std::endl;

    std::cout << "new front:" << *dq.begin() << std::endl;
    dq.insert(dq.begin() + 1, 8);
    std::cout << "n:" << n << std::endl;   // 往后插入元素后，引用和迭代器也可能有效
    std::cout << "iter:" << *iter << std::endl;

    std::deque<int> dq_2;
    auto iter_2 = dq_2.begin();  
    dq_2.push_back(18);
    dq_2.push_back(8);
    int& n_2 = dq_2.front();  
    std::cout << "iter_2:" << *iter_2 << std::endl;
    std::cout << "n_2:" << n_2 << std::endl;   
    // dq.insert(dq_2.begin() + 1, 6);
    std::cout << "n_2:" << n_2 << std::endl;     // 迭代器和引用均失效
    std::cout << "iter_2:" << *iter_2 << std::endl;

    std::vector<int> nums{1,2,3, 2,5,3,6,1,1,3,2,4,3,6,7,7,8,5,7,3,5,2,5,6,4,3,5,6,7,5};

    float avg = 0;
    float var = 0;
    int N = 1; 

    for (const int& n : nums) {
      if (N > 1) {
        var = var * (N - 2) / (N - 1)
            + pow((n - avg), 2) / N; 
      // } else {
      //   var = pow((n - avg), 2) / N; 
      }
      avg += (n - avg) / N; 
      ++N;
    }
    std::cout << "avg: " << avg << ", var: " << var << std::endl;

    avg = 0; var = 0;
    for (const int& n : nums) {
      avg += n; 
    }
    avg /= nums.size(); 
    for (const int& n : nums) {
      var += (n - avg) * (n - avg); 
    }
    var /= (nums.size() - 1); 
    std::cout << "avg: " << avg << ", var: " << var << std::endl;
    return 0;  
}





















