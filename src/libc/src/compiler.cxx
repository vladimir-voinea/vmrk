#include <compiler.hpp>
#include <stdlib.h>

namespace __cxxabiv1 
{ 
	extern "C" int __cxa_guard_acquire (__guard *g) 
	{
		return !*(char *)(g);
	}
 
	extern "C" void __cxa_guard_release (__guard *g)
	{
		*(char *)g = 1;
	}
 
	extern "C" void __cxa_guard_abort (__guard *)
	{
 
	}
}

__attribute__((noreturn))
extern "C" void __stack_chk_fail(void)
{
	abort();
}