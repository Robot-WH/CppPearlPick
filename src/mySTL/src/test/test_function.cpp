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
#include "tuple.hpp"
#include "index_sequence.hpp"
#include "param_wrapper.hpp"

class Print {
	public:
		Print() {}
		virtual ~Print() {}
		int draw(int a, int b, int c)
		{
			std::cout << "a = " << a << "," << "b = " << b << "," << "c = " << c << "\n";
			return 0;
		}
};

 std::string print(int a, int b, int c) {
	std::cout << "a = " << a << "," << "b = " << b << "," << "c = " << c << "\n";
	return std::string("hahaha");
}

template<typename ... __args_type>
class printTuple {

	public:
		printTuple(__args_type ... args) : my_args_(args ...) {} 

		// 仿函数
		auto operator()() {
			return print(mk_ind_seq_);  
		}

		template<size_t ... __index, typename... __Args>    //  __Args 是占位符参数  
		void print(mySTL::index_sequence<__index...>, __Args... args) {
			int array[] = {(std::cout<<mySTL::param_wrapper<decltype(mySTL::get<__index>(my_args_))>(mySTL::get<__index>(my_args_), args...)<<std::endl, 0)...};
		}



	private:
		mySTL::make_index_sequence<sizeof...(__args_type)> mk_ind_seq_;     // 构造出 index_sequence 
		mySTL::tuple<__args_type ...> my_args_;      // 保存全部的参数信息  

};

// 构造 printTuple 对象  
template<typename... args_type>
printTuple<args_type...> make_printTuple(args_type... args) {
	return printTuple<args_type...>(args...);
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

	auto print_tuple = make_printTuple('c', 1, "hello", 3.3, "yeah", 100, -89, 7.67884);
	print_tuple();  



    return 0;  
}




