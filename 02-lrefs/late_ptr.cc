/*
    compiled w/ g++ -O0 -fno-asynchronous-unwind-tables -fno-dwarf2-cfi-asm -masm=intel -fno-stack-protector late_ptr.cc
*/

#include <cstdio>

long a = 1;

void goo(long* *ptr_) {
        long b = 7;
        *ptr_ = &b; 
        //printf("%d\n", **ptr_);
        return;
}

void goo2(long c) {
        long b = 8;
        return;
}

int main() {
        long *ptr = &a; 
        printf("%ld\n", *ptr);
        goo(&ptr);
        printf("%ld\n", *ptr);
        goo2(10);
        printf("%ld\n", *ptr);
}

