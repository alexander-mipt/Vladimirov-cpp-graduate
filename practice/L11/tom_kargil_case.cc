/*
	in case of throwing exception Destructor does not called implicitly.
*/
#include <iostream>

class A {
public:
	A(int x = 0) {
		std::cout << "Constructor\nStart disk formating" << std::endl;
		if (x != 0) {
			throw 1;
		}	
	}
	~A() {
		std::cout << "Destructor\nEnd disk formating" << std::endl;
	}
};

int main() {
	try {
		A obj{};
	}
	catch(int x) {
		std::cout << "catched " << x << std::endl;
	}
}
