#include <iostream>
/*
Dynamic PVC error
*/
struct Base {
	Base() { unsafe(); } // PVC invocation
	virtual void doIt() = 0;
	void unsafe() { doIt(); }
};

struct Derived : public Base { 
	void doIt() override {
		std::cout << "hello" << std::endl;
	}
};

int main() {
	Derived d;
}
	
