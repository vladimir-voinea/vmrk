#include <stdio.h>
#include <stdlib.h>
 
__attribute__((__noreturn__))
extern "C" void abort(void) {
	printf("kernel: panic: abort()\n");
    asm volatile("hlt");
	__builtin_unreachable();
}