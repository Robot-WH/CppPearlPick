
#ifndef SCOPED_ARRAY_HPP_
#define SCOPED_ARRAY_HPP_

#include <iostream>
#include <memory>

namespace my {

    template<typename _T>
    class scoped_array
    {
        public:
            scoped_array(_T *p = nullptr) : p_(p)
            {
            }
            ~scoped_array()
            {
                delete [] p_;     // 注意数组的空间释放
            }

            scoped_array(const scoped_array<_T>&) = delete;
            const scoped_array<_T>& operator=(const scoped_array<_T>&) = delete;
            void operator==(const scoped_array<_T>&)  const = delete;
            void operator!=(const scoped_array<_T>&)  const = delete;

            typedef scoped_array<_T> this_type;  

            void reset(_T *p = nullptr)
            {
                this_type(p).swap(*this);
            }
            // 重载[]
            _T& operator[](int i)
            {
                return *(p_ + i);
            }
            // get方法获得 指针本身
            _T* get() const
            {
                return p_; 
            }

        protected:
            // 交换指针
            void swap(scoped_array& sp)
            {
                _T *tmp = sp.p_;
                sp.p_ = p_;
                p_ = tmp;   
            }
         
        private:
            _T *p_;
    }; // class scoped_array
};  // namespace my

#endif