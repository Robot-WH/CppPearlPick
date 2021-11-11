
#include <iostream>
#include <memory>
#include <boost/smart_ptr.hpp>
#include "scoped_ptr.hpp"

using namespace std;
using namespace boost;  

int main()
{
    int *p = new int(10);
    // boost::scoped_ptr<int> sp(p);
    my::scoped_ptr<int> sp(p);  
    cout<<"p: "<<*sp<<endl;
    string *s = new string("hello");
    my::scoped_ptr<string> sp_2(s);
    cout<<"s size: "<<sp_2->size()<<endl;
    // my::scoped_ptr<int> sp_3(sp);
    // sp_3 = sp;
    // reset
    int *p_2 = new int(100);
    sp.reset(p_2);
    cout<<"reset p: "<<*sp<<endl;
    return 0;  
}

