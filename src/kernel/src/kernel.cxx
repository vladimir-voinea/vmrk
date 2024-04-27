#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <bootstrap.hpp>

void foo(const char* str)
{
	char buffer[16];
	memcpy(buffer, str, strlen(str));
}
 
extern "C" void Kernel_Main(void) 
{
	printf("vmr kernel started\n");
	printf("Long mode is %s\n", is_long_mode_available() ?  "available" : "not available");
}