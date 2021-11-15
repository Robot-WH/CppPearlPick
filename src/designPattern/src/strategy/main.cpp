#include "common.h"

// 策略模式 + 工厂模式 

class TaxStrategy {
    public:
        virtual ~TaxStrategy() {}
        virtual double Calculate() = 0;
};

class CNTax : public TaxStrategy {
    public:
         virtual double Calculate() {
            std::cout<<"Calculate CNTax"<<std::endl;
         }
};

class USTax : public TaxStrategy {
    public:
         virtual double Calculate() {
            std::cout<<"Calculate USTax"<<std::endl;
         }
};

class JPTax : public TaxStrategy {
    public:
         virtual double Calculate() {
             std::cout<<"Calculate JPTax"<<std::endl;
         }
};

// 工厂模式
// 工厂基类
class StrategyFactoryBase {
    public:
        virtual ~StrategyFactoryBase() {}
        virtual boost::shared_ptr<TaxStrategy> NewStrategy() = 0;   
};  
// 中国工厂
class CNStrategyFactory : public StrategyFactoryBase {
    public:
        boost::shared_ptr<TaxStrategy> NewStrategy() override {
            return boost::make_shared<CNTax>() ;   
        }
};

// 美国工厂
class USStrategyFactory : public StrategyFactoryBase {
    public:
        boost::shared_ptr<TaxStrategy> NewStrategy() override {
            return  boost::make_shared<USTax>() ;   
        }
};

// 日本工厂
class JPStrategyFactory : public StrategyFactoryBase {
    public:
        boost::shared_ptr<TaxStrategy> NewStrategy() override {
            return boost::make_shared<JPTax>() ;   
        }
};


// 稳定  ！！
class Sales {
    public:
        Sales(boost::shared_ptr<StrategyFactoryBase> pFactory) {
            strategy_ = pFactory->NewStrategy();     // 采用抽象工厂模式创建  
        }
        // 赋值
        Sales& operator=(const Sales &sl) {
            std::cout<<" operator = "<<std::endl;
            strategy_ = sl.strategy_;  
        }
        // 移动构造
        Sales& operator=(const Sales &&sl) {
            std::cout<<" move construct = "<<std::endl;
            strategy_ = sl.strategy_;  
        }

        ~Sales() {
            std::cout<<"free Sales"<<std::endl;
        }

        double CalculateTax() {
            return strategy_->Calculate();  
        }

        // 留出接口
        void set_strategy(boost::shared_ptr<StrategyFactoryBase> pFactory) {
            strategy_ = pFactory->NewStrategy();     // 采用抽象工厂模式创建  
        }
       
    private:
        boost::shared_ptr<TaxStrategy> strategy_;                                   // 计算的策略
};


int main()
{
    Sales sales{boost::make_shared<CNStrategyFactory>()};
    sales.CalculateTax();   
    sales = Sales{boost::make_shared<USStrategyFactory>()};      // 匿名赋值       触发移动构造
    sales.CalculateTax();   
    sales = Sales{boost::make_shared<JPStrategyFactory>()};  
    sales.CalculateTax();   
    return 0;   
}