#include <iostream>

int main() {
	int *p = new int[5];
	int &x = p[3];
	x = 1;
	delete [] p;
	x += 1; // it ceased to be
	std::cout << x << std::endl;
}
