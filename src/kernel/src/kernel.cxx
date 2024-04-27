#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <bootstrap.hpp>
 
/* Check if the compiler thinks you are targeting the wrong operating system. */
#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif
 

void foo(const char* str)
{
	char buffer[16];
	memcpy(buffer, str, strlen(str));
}
 
extern "C" void kernel_main(void) 
{
	printf("Hello world\n");

	const auto long_mode_available = is_long_mode_available();
	printf("Long mode is %s\n", long_mode_available ?  "available" : "not available");
}