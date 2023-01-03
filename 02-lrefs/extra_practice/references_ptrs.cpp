#include <iostream>
#define $(x) std::cout << #x << "\t= " << x << std::endl

int main() {
	int v{1};
	const int c{2};
	int *ptr = &v;
	const int *ptr_c = &v;
	int * const c_ptr = &v;
	// c_ptr = &c; // error	
	// *ptr_c = 2; // error
	
	$(ptr);
	$(ptr_c);
	$(c_ptr);

	const int &c_ref = v;
	int &ref = c; // error
	$(c_ref);
	$(ref);

	return 0;
}
