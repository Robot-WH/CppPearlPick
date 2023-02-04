
#pragma once 

namespace mySTL {

// 分配内存
template<typename _Ty> 
_Ty* Allocate(size_t N, _Ty*) {
    if (N < 0) {
        N = 0;
    }
    // operator new() 和 new 的关系: 1. operator new() 是函数, new 是运算符 
    //     2. new的内部: 调用operator new() => 调用构造函数
    return (_Ty*)operator new(N * sizeof(_Ty)); 
}

template<typename _T1, typename _T2>
void Construct(_T1* p, const _T2& v) {
    new ((void*)p) _T1(v);   // placement new     在p所指的内存空间中构造v
}

template<typename _Ty>
void Destory(_Ty* p) {
    p->~_Ty(); 
}


template<typename _Ty>
class Allocator {
    public:
        using size_type = size_t;
        using difference_type = int;
        using pointer = _Ty*;
        using const_pointer = const _Ty*;   // 指向常量的指针变量
        using reference = _Ty&;
        using const_reference = const _Ty&;
        using value_type = _Ty;

        // 返回地址
        pointer address(reference x) const {
            return &x;
        }

        const_pointer address(const_reference x) const {
            return &x;
        }
        // 分配内存
        pointer allocate(size_type n, const void*) {
            return Allocate(n, (pointer)nullptr);
        }
        // 对char单独分配
        char* charAlloc(size_type n) {
            return Allocate(n, (char*)nullptr);
        }
        // 析构内存
        void deAllocate(void* p, size_type) {
            operator delete(p);
        }
        // 构造
        void construct(pointer p, const _Ty& v) {
            Construct(p, v);
        }
        // 析构
        void destory(pointer p) {
            Destory(p);
        }
        size_t max_size() {
            // size_t N = 
        }
};

}
