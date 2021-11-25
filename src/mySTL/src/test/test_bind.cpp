/*
 * @Copyright(C): Your Company
 * @FileName: 文件名
 * @Author: 作者
 * @Version: 版本
 * @Date: 2021-11-24 20:13:28
 * @Description: 
 * @Others: 
 */

#include "common.hpp"
 #include "bind.hpp"

class Print
{
public:
	Print() {}
	virtual ~Print() {}
	int draw(int a, int b, int c)
	{
		std::cout << "a = " << a << "," << "b = " << b << "," << "c = " << c << "\n";
		return 0;
	}
};


 int print(int a, int b, int c)
{
	std::cout << "a = " << a << "," << "b = " << b << "," << "c = " << c << "\n";
	return 0;
}
 
int main() {

    mySTL::binder<int(*)(int, int, int)> f{print};     // 不允许隐式类型转换 
    f(1,2,3); 
    Print pt;  
    mySTL::mbinder<int(Print::*)(int, int, int), Print> f2{&Print::draw, &pt}; 
    f2(1,2,3);
    auto f3 = mySTL::bind(&print);
	f3(1, 2, 3);
 
	auto f4 = mySTL::bind(&Print::draw, &pt);
	f4(1, 2, 3);
    return 0;  
}



