#include <memory>
#include <iostream>
#include <map>


class B {
    public:
    virtual ~B() = default;
    virtual int foo() const  = 0;
};

class Ab final : public B {
    public:
    int foo() const override { return 1; }
};

class Bb final : public B {
    public:
    int foo() const override { return 2; }
};

void foo(std::unique_ptr<B> &ptr) {
    std::cout << ptr->foo() << std::endl;
}



int main() {
    std::unique_ptr<B> m(new Ab{});
    foo(m);
}
