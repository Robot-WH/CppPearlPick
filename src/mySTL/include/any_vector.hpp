/*
 * @Copyright(C): Your Company
 * @FileName: 文件名
 * @Author: 作者
 * @Version: 版本
 * @Date: 2022-04-18 22:08:40
 * @Description: 
 * @Others: 
 */

#pragma once 

#include <vector>
#include <memory>
#include <typeindex>

namespace mySTL {

    class BaseVector
    {
        public:
            virtual ~BaseVector() {}
            //virtual std::unique_ptr<BaseVector> Clone() const = 0; 
            virtual std::type_index GetType() const = 0; 
    };

    // Any 实际数据存储的地方 
    template<typename _T>
    class DataVector : public BaseVector 
    {
        public:
            DataVector() : type(typeid(_T))
            {
            }

            std::type_index GetType() const override
            {
                return type;
            }

            std::vector<_T> values;
            std::type_index type;  
    };

    /**
     * @brief: 非模板类  但是可以存储任意类型的数据 
     * @details: 
     * @param {*}
     * @return {*}
     */    
    class AnyVector
    {
        public:

            AnyVector() {}
            ///////////////////////////////////////////////////
            // 判断类型是否相同    
            template<class _T> bool Is() const
            {
                return base_ptr->GetType() == std::type_index(typeid(_T));    // typeid操作符的返回结果是名为type_info的标准库类型的对象的引用
            }

            template<class _T>
            void Registration()
            {
                base_ptr = std::unique_ptr<BaseVector>(new DataVector<_T>());
            }

            // 添加数据
            template<class _T>
            void AddData(_T&& data)
            {
                // 首先判断类型是否一致
                if (!Is<_T>())
                {
                    throw std::bad_cast();  
                }
                dynamic_cast<DataVector<_T>*>(base_ptr.get())->values.push_back(std::forward<_T>(data)); 
                std::cout<<"data size: "<<dynamic_cast<DataVector<_T>*>(base_ptr.get())->values.size()<<std::endl;
            }

            template<class _T>
            _T GetValue(uint16_t n)
            {
                // 首先判断类型是否一致
                if (!Is<_T>())
                {
                    throw std::bad_cast();  
                }
                if (n >= dynamic_cast<DataVector<_T>*>(base_ptr.get())->values.size())  return _T();  
                return dynamic_cast<DataVector<_T>*>(base_ptr.get())->values[n];  
            }

        private:
            std::unique_ptr<BaseVector> base_ptr;
    };

}
