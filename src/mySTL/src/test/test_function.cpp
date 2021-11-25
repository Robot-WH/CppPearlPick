/*
 * @Copyright(C): Your Company
 * @FileName: 文件名
 * @Author: 作者
 * @Version: 版本
 * @Date: 2021-11-25 13:09:15
 * @Description: 
 * @Others: 
 */

#include "common.hpp"
#include "function.hpp"

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


 std::string print(int a, int b, int c)
{
	std::cout << "a = " << a << "," << "b = " << b << "," << "c = " << c << "\n";
	return std::string("hahaha");
}
 
int main() {

	mySTL::function<std::string, int, int, int> f1 = mySTL::bind(&print); 
	std::cout<<"f1 func return: " << f1(1,2,3) << std::endl;

	mySTL::function<std::string(int, int, int)> f2 = mySTL::bind(&print); 
	std::cout<<"f2 func return: " << f2(1,2,3) << std::endl;
	
	Print print;   
	mySTL::function<int(int, int, int)> f3 = mySTL::bind(&Print::draw, &print); 
	std::cout<<"f3 func return: " << f3(1,2,3) << std::endl;

	// TODO: 实现直接用函数赋值  
	// mySTL::function<std::string(int, int, int)> f4 = print;  

    return 0;  
}




