/*
 * @Copyright(C): Your Company
 * @FileName: 文件名
 * @Author: 作者
 * @Version: 版本
 * @Date: 2022-03-03 23:18:30
 * @Description: 
 * @Others: 
 */
#pragma once 

namespace mySTL {

    /**
     * @brief:  vector的简单尝试   
     * @details 迭代器没有实现 
     */    
    template<class _ValueT>
    class simple_vector
    {
        public:
            using value_type                     = _ValueT;
            using reference                        = _ValueT&;
            using const_reference           = const _ValueT&;

            using iterator                              = _ValueT*;
            using const_iterator                = const _ValueT*;

            using size_type                          = ::size_t;      // :: 表示从全局作用域找  
            using difference_type             = ::ptrdiff_t;   
        private:
            _ValueT *m_data_;
            ::size_t m_size_;
            ::size_t m_capacity_;  

        public:
            constexpr
            simple_vector() noexcept
                : m_data_(), m_size_(), m_capacity_()
            {}

            ~simple_vector()
            {

            }
            // 拷贝构造
            simple_vector(const simple_vector& rhs)
            {
                // 分配内存
                m_data_ = static_cast<_ValueT*>(::operator new(rhs.m_capacity_ * sizeof(_ValueT)));
                
            }
            
    };

}