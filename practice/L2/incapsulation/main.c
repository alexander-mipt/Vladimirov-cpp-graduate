#include "interface.h"
#include "stdio.h"

int main() {
	private* obj = constructor();
	if (obj == NULL) {
		return -1;
	}
	print(obj);
}
