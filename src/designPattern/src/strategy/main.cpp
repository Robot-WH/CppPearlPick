#include "common.h"

class Context
{
private:
    /* data */
public:
    Context(/* args */);
    ~Context();
};


class TaxStrategy {
    public:
        virtual ~TaxStrategy() {}
        virtual double Calculate(const Context& context) = 0;
};

class CNTax : public TaxStrategy {
    public:
         virtual double Calculate(const Context& context) {

         }
};

class USTax : public TaxStrategy {
    public:
         virtual double Calculate(const Context& context) {
             
         }
};

class JPTax : public TaxStrategy {
    public:
         virtual double Calculate(const Context& context) {
             
         }
};

// 稳定  ！！
class Sales {
    public:
        Sales(StrategyFactory *factory) {
            strategy_ = factory->NewStrategy();     // 采用抽象工厂模式创建  
        }

        ~Sales() {
            delete strategy_;  
        }

        double CalculateTax(const Context& context) {
            double val = strategy_->Calculate(context);  
        }
       
    private:
        TaxStrategy *strategy_;      // 计算的策略
};


int main()
{

    return 0;   
}