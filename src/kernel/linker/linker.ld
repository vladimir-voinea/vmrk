ENTRY(_start)

SECTIONS
{
  . = 4M;
  _kernel_physical_start = .;

  .boottext :
    {
      ../arch/x86_64/libboot.a (.multiboot)
      ../arch/x86_64/libboot.a (.text)
    }
  .bootrodata :
    {
      ../arch/x86_64/libboot.a (.rodata)
    }
  .bootdata :
    {
      ../arch/x86_64/libboot.a (.data)
    }
  .bootbss :
    {
      ../arch/x86_64/libboot.a (.bss)
      ../arch/x86_64/libboot.a (COMMON)
    }

  . = ALIGN(0x1000);
  _boot_end = .;

  . += 0xFFFFFFFF80000000;
  _kernel_virtual_start = .;
  .text : AT(_boot_end)
  {
    *(.multiboot)
    *(.text)
  }

  . = ALIGN(0x1000);

  .rodata : AT(ALIGN(LOADADDR(.text) + SIZEOF(.text) + 0x1000, 0x1000))
  {
      *(.rodata)
  }

  .data : AT(ALIGN(LOADADDR(.rodata) + SIZEOF(.rodata) + 0x1000, 0x1000))
  {
      *(.data)
  }

  . = ALIGN(0x1000);

  .bss : AT(ALIGN(LOADADDR(.data) + SIZEOF(.data) + 0x1000, 0x1000))
  {
    *(COMMON)
    *(.bss)
  }

  _kernel_virtual_end = .;

  _kernel_physical_end = (LOADADDR (.bss) + SIZEOF (.bss) + 0x1000) & 0xFFFFFFFFFFFFF000;
}
