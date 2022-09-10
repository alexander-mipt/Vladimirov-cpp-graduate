#include <iostream>

class A {
const int m_a{0};
public:
	A(int a) : m_a{a} {}
	void print() { std::cout << m_a << std::endl; }
};

int main() {
	A obj(4);
	obj.print();
}
