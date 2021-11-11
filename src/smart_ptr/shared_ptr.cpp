

#include <iostream>
#include <memory>
#include <boost/smart_ptr.hpp>
#include "shared_ptr.hpp"

using namespace std;
using namespace boost;  


int main()
{
    int *p = new int(10);
    my::shared_ptr<int> sp(p);  
   
    return 0;  
}

