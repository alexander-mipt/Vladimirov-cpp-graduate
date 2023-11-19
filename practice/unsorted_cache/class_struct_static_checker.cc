/*
    This example demonstrates, how to create typechecker for
    public entities of any class or struct
    using concepts
    Warning: i don't know how to check private entities
    x86_64 g++ 12.2 -std=c++20
*/

#include <iostream>


class A {
    public:
    enum State {
        a,
        b
    };
    int field;
    void method() {}
};

class B {

};

template <typename T>
concept hasType = requires {
    typename T::State;
};

template<typename T>
concept hasField = requires (T o) {
    o.field;
};

template<typename T>
concept hasMethod = requires (T o) {
    {o.method()} -> std::same_as<void>;
};

template<typename T>
concept typeChecker = requires {
    requires hasType<T>;
    requires hasField<T>;
    requires hasMethod<T>;
}; 

template<typeChecker T>
class C {
};

int main() {
    C<A> f;
}
