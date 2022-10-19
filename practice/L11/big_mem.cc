#include <iostream>
constexpr unsigned long long size = 1'000'000'000'000'000;
int main() {
	// int* ptr_ = nullptr;
	// delete ptr_;
	try {
		auto* ptr = new int[size];
	}
	//delete ptr;
	catch(std::exception& e) {
		std::cerr << "Catched " << e.what() << std::endl;
	}
}
