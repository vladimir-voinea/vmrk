#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
/* Check if the compiler thinks you are targeting the wrong operating system. */
#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif
 
/* This tutorial will only work for the 32-bit ix86 targets. */
#if !defined(__i386__)
#error "This tutorial needs to be compiled with a ix86-elf compiler"
#endif

void foo(const char* str)
{
	char buffer[16];
	memcpy(buffer, str, strlen(str));
}
 
extern "C" void kernel_main(void) 
{
	printf("Hello mofo\n");

	foo("asdhndsafhhdsihfksdafhfjsdahfksadhfashd");

	printf("Back");
}