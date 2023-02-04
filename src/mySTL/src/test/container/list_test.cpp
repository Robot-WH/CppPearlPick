
#include<ostream>
#include <iostream>
#include <stdio.h>
#include<cstring>
#include "common.hpp"
#include "container/list/list.hpp"
#include <memory>
#include <unordered_map>
#include<iomanip>

using namespace mySTL;

class string {
    public:
        string(const char* str = "") {
            m_data = new char(strlen(str) + 1);
            strcpy(m_data, str);   // str 拷贝到 m_data
        }
        ~string() {
            delete[] m_data;
            m_data = nullptr; 
        }
        
        friend std::ostream& operator <<(std::ostream& a, string& b) {
            a << b.m_data;
            return a;
        }

    private:
        char* m_data;
};

static size_t ROUND_UP(size_t bytes) {
    return ((bytes + 8 - 1) & ~(8 - 1));
}

int main() 
{
    std::cout<<"list test"<<std::endl;
    list<int> data;
    data.push_back(20);
    data.push_back(30);
    data.push_front(60);
    data.pop_front();
    for (auto it = data.begin(); it != data.end(); it++) {
        std::cout<<"it: "<<*it<<std::endl;
    }
    {
        list<string> str_list;
        string s("abc");
        str_list.insert(str_list.begin(), s);
        for (auto it = str_list.begin(); it != str_list.end(); it++) {
            std::cout<<"it: "<<*it<<std::endl;
        }
       list<int>::const_iterator c_it = data.begin(); 
    }

    double a = 0.30000000000000; 
    std::cout<<std::setprecision(20)<<"a:"<<a<<std::endl;

    return 0;  
}