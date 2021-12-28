/*
 * @Copyright(C): Your Company
 * @FileName: 文件名
 * @Author: 作者
 * @Version: 版本
 * @Date: 2021-12-07 20:13:43
 * @Description: 
 * @Others: 
 */

#include "shared_ptr.hpp"

namespace my {
    template<typename T, typename... Ts>
    shared_ptr<T> make_shared(Ts&&... params) {   // 形参为万能引用  
        return shared_ptr<T>(new T(std::forward<Ts>(params)...));  // forward 完美转发 
    }
};
