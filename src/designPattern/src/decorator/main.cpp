/*
 * @Copyright(C): Your Company
 * @FileName: 
 * @Author: lwh
 * @Version: 
 * @Date: 2021-11-17 19:56:26
 * @Description:  decorator模式的实现
 * @Others:  主要场景如下： 
 */

#include "common.h"

//  烹饪基类  
class CookingBase {
    public:
        virtual ~CookingBase() {}
        // 不同的做法
        virtual void Fry() = 0;            // 炒
        virtual void braiser() = 0;    //  蒸
        virtual void boil() = 0;          // 煮
};

// 烹饪肉类
class CookingMeat : public CookingBase {
    public:
        void Fry() override {

        }
        void braiser() override {

        }
        virtual void boil() override {

        }
};

// 烹饪蔬菜   
class CookingVege : public CookingBase {
    public:
        void Fry() override {

        }
        void braiser() override {

        }
        virtual void boil() override {

        }
};


// 烹饪饭
class CookingRice : public CookingBase {
    public:
        void Fry() override {

        }
        void braiser() override {

        }
        virtual void boil() override {

        }
};

///   继续对烹饪进行扩展 

/**
 * @brief: 
 * @details: 
 * @param {*}
 * @return {*}
 */
int main()
{

    return 0; 
}
