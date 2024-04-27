#include <bootstrap.hpp>
#include <stdint.h>

void cpuid(uint32_t& eax, uint32_t &ebx, uint32_t &ecx, uint32_t &edx)
{
    asm volatile("cpuid"
                 : "=b"(ebx), "=c"(ecx), "=d"(edx)
                 : "a"(eax)
                 : "memory");
}

bool is_long_mode_available()
{
    uint32_t eax, ebx, ecx, edx;
    cpuid(eax, ebx, ecx, edx);
    if (eax < 0x80000001)
    {
        return false;
    }

    cpuid(eax, ebx, ecx, edx);
    return edx & (1 << 29);
}
