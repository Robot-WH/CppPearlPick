/*
 * @Copyright(C): Your Company
 * @FileName: 文件名
 * @Author: 作者
 * @Version: 版本
 * @Date: 2021-11-28 14:56:48
 * @Description: 
 * @Others: 
 */

#include "common.h"

using namespace std;  
//  烹饪基类  
class CookingBase {
    public:
        virtual ~CookingBase() {}
        // 不同的做法
        virtual void Chinese() = 0;            // 中餐
        virtual void America() = 0;           // 西餐 
        virtual void Japen() = 0;                   // 日式
};

// 烹饪肉类
class CookingMeat : public CookingBase {
    public:
        void Chinese() override {
            // 以下是不同的实现....
            std::cout<<"do Chinese meat"<<endl;
        }
        void America() override {
            std::cout<<"do  America meat"<<endl;
        }
        virtual void Japen() override {
            std::cout<<"boil Japen meat"<<endl;
        }
};

// 烹饪蔬菜   
class CookingVege : public CookingBase {
    public:
        void Chinese() override {
            std::cout<<"do Chinese Vege"<<endl;
        }
        void America() override {
            std::cout<<"do America Vege"<<endl;
        }
        virtual void Japen() override {
            std::cout<<"do Japen Vege"<<endl;
        }
};


// 烹饪饭
class CookingRice : public CookingBase {
    public:
        void Chinese() override {
            std::cout<<"do Chinese Rice"<<endl;
        }
        void America() override {
            std::cout<<"do America Rice"<<endl;
        }
        virtual void Japen() override {
            std::cout<<"do Japen Rice"<<endl;
        }
};

///   继续对烹饪进行扩展 
class DecoratorCooking : public CookingBase {  // public CookingBase  是为了继承基类的接口 ，这是因为要对接口进行扩展 
    protected:
        CookingBase *cooking_;      // 被装饰的对象 - 即烹饪这个过程           同时继承与组合    装饰模式的特点  
        DecoratorCooking(CookingBase *base) : cooking_(base) {}
};


// 装饰的具体实现  
// 烹饪之前先清理
class CookingAndClear : public  DecoratorCooking {    
    public: 
        CookingAndClear(CookingBase *base) : DecoratorCooking(base) {}
        // 下面是被扩展的接口  
        void Chinese() override {
            // 增加额外的清理工作  
            std::cout<<"chinese clear"<<endl;                      // 对于 meat, vege, rich 的clear都是相同的
            cooking_->Chinese();                               // 只有这里不同 !!!!!!!
        }
        void America() override {
            std::cout<<"America clear"<<endl;
             cooking_->America();    // 只有这里不同 !!!!!!!
        }
        virtual void Japen() override {
            std::cout<<"Japen clear"<<endl;
            cooking_->Japen();     // 只有这里不同 !!!!!!!
        }
};

// 烹饪后打包 
class CookingAndPackage : public  DecoratorCooking {
    public: 
        CookingAndPackage(CookingBase *base) : DecoratorCooking(base) {}

        void Chinese() override {
            cooking_->Chinese();          // 只有这里不同 !!!!!!!
            // 增加额外的打包工作  
            std::cout<<"Chinese Package"<<endl;
        }
        void America() override {
             cooking_->America();        // 只有这里不同 !!!!!!!
             // 增加额外的打包工作  
            std::cout<<"America Package"<<endl;
        }
        virtual void Japen() override {
            cooking_->Japen();       // 只有这里不同 !!!!!!!
            // 增加额外的打包工作  
            std::cout<<"Japen Package"<<endl;
        }
};  


/**
 * @brief: 
 * @details: 
 * @param {*}
 * @return {*}
 */
int main()
{
    CookingAndClear meat_cooking_clear{new CookingMeat{}}; 
    meat_cooking_clear.Chinese();   

    CookingAndPackage vege_cooking_clear{new CookingVege{}};
     vege_cooking_clear.Japen();  
    return 0; 
}
