/*
 * @Copyright(C): Your Company
 * @FileName: 文件名
 * @Author: 作者
 * @Version: 版本
 * @Date: 2021-12-07 20:13:54
 * @Description: 
 * @Others: 
 */

#include "scoped_ptr.hpp"

namespace my {
    template<typename T, typename... Ts>
    scoped_ptr<T> make_scoped(Ts&&... params) {   // 形参为万能引用  
        return scoped_ptr<T>(new T(std::forward<Ts>(params)...));  // forward 完美转发 
    }
};