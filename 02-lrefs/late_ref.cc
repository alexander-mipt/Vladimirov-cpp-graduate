#include <iostream>
int& foo () {
	int x = 42;
	return x;
}
int main() {
//	int x = foo();	// it expired and gone
	//int &a0 = 1; // error
	int const &a = 2; // ok
	int b = a;
	std::cout << b << std::endl;
}
