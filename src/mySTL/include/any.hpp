/*
 * @Copyright(C): Your Company
 * @FileName: 文件名
 * @Author: 作者
 * @Version: 版本
 * @Date: 2022-04-18 17:48:09
 * @Description: 
 * @Others: 
 */

#pragma once 

#include <memory>
#include <typeindex>

namespace mySTL {

    class Base
    {
        public:
            virtual ~Base() {}
            virtual std::unique_ptr<Base> Clone() const = 0; 
    };
    
    // Any 实际数据存储的地方 
    template<typename _T>
    class Data : public Base 
    {
        public:
            Data(_T const& t) : value(t)
            {}
            // 返回Data的拷贝对象 
            std::unique_ptr<Base> Clone() const override
            {
                return std::unique_ptr<Base>(new Data<_T>(value));
            }

            _T value;  
    };

    class Any 
    {
        public:
            Any() : type(typeid(void)) {}
            // 拷贝构造 
            Any(Any const& a) : base_ptr(a.base_ptr->Clone())
                                                    ,type(a.type) {}
            // 移动构造
            Any(Any&& a) : base_ptr(std::move(a.base_ptr))
                                            ,type(a.type) {}
            // 模板构造
            template<typename _T>
            Any(_T&& t) : base_ptr(new Data<_T>(std::forward<_T>(t)))
                                        , type(typeid(_T))
            {
                std::cout<<"copy construct"<<std::endl;
                std::cout<<"type: "<<type.name()<<std::endl;
            }

            Any& operator= (Any const& a)
            {
                std::cout<<"operator="<<std::endl;
                if (base_ptr == a.base_ptr)
                    return *this;    // 指向同一个数据对象  则赋值没有意义  直接返回当前类对象
                base_ptr = a.base_ptr->Clone();
                type = a.type; 
                std::cout<<"type: "<<type.name()<<std::endl;
                return *this;  
            }

            ///////////////////////////////////////////////////
            // 判断类型是否相同    
            template<class _T> bool Is() const
            {
                return type == std::type_index(typeid(_T));    // typeid操作符的返回结果是名为type_info的标准库类型的对象的引用
            }

            ///////////////////////////////////////////////////
            // 提取数据  
            template<typename _T>
            _T Cast() 
            {
                // 先判断类型是否一致
                if (!Is<_T>())
                {
                    std::cerr<<"Type Error !"<<std::endl;
                    throw std::bad_cast();  // 抛出类型转换错误   
                }
                return dynamic_cast<Data<_T>*>(base_ptr.get())->value;
            }   

        private:
            // std::unique_ptr<Base> clone() const
            // {
            //     if (base_ptr != nullptr)
            //         return base_ptr->Clone();
            //     return nullptr;  
            // }
            std::unique_ptr<Base> base_ptr;
            std::type_index type;  
    };
}
