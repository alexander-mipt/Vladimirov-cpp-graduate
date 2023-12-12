/*
    How to use shared ptr in deep & default copy context
    g++ -DCOPY_PTR deep_copy.cc
*/

#include <array>
#include <memory>
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <cstdint>
#include <vector>
#include <bitset>

#define COPY_PTR

class Z {
    public:
    Z() = default;
    Z(int label) : m_label(label) {}
    Z(const Z& obj) {
        std::cout << "Copied\n";
        m_label = obj.m_label;
    }
    void print() {
        std::cout << m_label << std::endl;
    }
    int m_label{0};
};

class A {
public:
    A(int label) : m_ptr(new Z{label}) {}
    #ifdef COPY_PTR
    A(const A& other) {
        m_ptr = std::make_shared<Z>(*other.m_ptr.get());
    }
    #endif
    void print() {
        m_ptr->print();
    }
    std::shared_ptr<Z> m_ptr{nullptr};
};


int main() {

    A obj1{3};
    obj1.print();
    A obj2 = obj1;
    obj1.m_ptr->m_label = 5;
    obj2.print();
    


    

}