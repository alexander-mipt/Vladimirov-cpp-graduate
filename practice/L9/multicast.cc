#include <iostream>
struct Base {
    int x{};
    virtual ~Base(){};
};
struct Derived : Base {};
int main() {
    Derived *dp = new Derived{};
    Base *bp = dp;
}
