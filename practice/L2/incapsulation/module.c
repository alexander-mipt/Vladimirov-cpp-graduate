#include "interface.h"
#include <stdio.h>
#include "stdlib.h"

typedef struct private {
	int val;
} private;

private *constructor() {
	private *ptr = (private*) malloc(sizeof(private));
	if (ptr == NULL) {
		return NULL;
	}
	ptr->val = 5;
	return ptr;
}

void print(const private* ptr) {
	if (ptr	== NULL) {
		printf("not found\n");
		return;
	}
	printf("val: %d\n", ptr->val);
	return;
}
