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

using namespace std;  
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
            std::cout<<"Fry meat"<<endl;
        }
        void braiser() override {
            std::cout<<"braiser meat"<<endl;
        }
        virtual void boil() override {
            std::cout<<"boil meat"<<endl;
        }
};

// 烹饪蔬菜   
class CookingVege : public CookingBase {
    public:
        void Fry() override {
            std::cout<<"Fry Vege"<<endl;
        }
        void braiser() override {
            std::cout<<"braiser Vege"<<endl;
        }
        virtual void boil() override {
            std::cout<<"boil Vege"<<endl;
        }
};


// 烹饪饭
class CookingRice : public CookingBase {
    public:
        void Fry() override {
            std::cout<<"Fry Rice"<<endl;
        }
        void braiser() override {
            std::cout<<"braiser Rice"<<endl;
        }
        virtual void boil() override {
            std::cout<<"boil Rice"<<endl;
        }
};

///   继续对烹饪进行扩展 
// 烹饪之前先清理
class CookingMeatAndClear : public CookingMeat {
    public: 
        void Fry() override {
            // 增加额外的清理工作  
            std::cout<<"clear"<<endl;
            CookingMeat::Fry();   
        }
        void braiser() override {
            std::cout<<"clear"<<endl;
             CookingMeat::braiser();   
        }
        virtual void boil() override {
            std::cout<<"clear"<<endl;
            CookingMeat::boil();   
        }
};

class CookingVegeAndClear : public CookingVege {
    public: 
        void Fry() override {
            // 增加额外的清理工作  
            std::cout<<"clear"<<endl;
            CookingVege::Fry();   
        }
        void braiser() override {
            std::cout<<"clear"<<endl;
             CookingVege::braiser();   
        }
        virtual void boil() override {
            std::cout<<"clear"<<endl;
            CookingVege::boil();   
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

    return 0; 
}
