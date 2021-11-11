
#include <iostream>
#include <memory>
#include <boost/smart_ptr.hpp>
#include "scoped_array.hpp"

using namespace std;
using namespace boost;  

int main()
{
    int *p = new int[10];
    my::scoped_array<int> sa(p);
    sa[1] = 10;

    return 0;  
}

