#include "common.h"

enum TaxBase {
    CN_Tax,
    US_Tax,
    JP_Tax
};



class Sales {
    public:

        // // 原始做法       违背 开闭原则  
        // double CalculateTax() {
            
        //     if (tax_ == CN_Tax) {

        //     } else if (tax_ == US_Tax) {

        //     } else if (tax_ == JP_Tax) {

        //     }
        // }

        double CalculateTax() {
            
            if (tax_ == CN_Tax) {

            } else if (tax_ == US_Tax) {

            } else if (tax_ == JP_Tax) {

            }
        }

    private:
        TaxBase tax_;
};


int main()
{

    return 0;   
}