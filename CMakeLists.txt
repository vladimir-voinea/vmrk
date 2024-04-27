cmake_minimum_required(VERSION 3.10)

project(vmrk LANGUAGES CXX)

set(TARGET "i686-elf-none")

enable_language(ASM)

set(CMAKE_ASM_COMPILER clang++)
set(CMAKE_ASM_FLAGS "-target ${TARGET}")

set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)

set(CMAKE_CXX_FLAGS "-target ${TARGET} -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti")
set(CMAKE_C_FLAGS "-target ${TARGET} -ffreestanding -O2 -Wall -Wextra")

set(CMAKE_CXX_STANDARD_LIBRARIES "")
set(CMAKE_C_STANDARD_LIBRARIES "")

add_executable(kernel
    src/boot/i686/boot.s
    src/kernel.cxx
)

set_target_properties(kernel PROPERTIES
    LINK_FLAGS "-target ${TARGET} -Wl -T ${CMAKE_SOURCE_DIR}/src/linker/linker.ld -nostdlib -ffreestanding"
)

# Create output directory structure
add_custom_command(TARGET kernel POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_BINARY_DIR}/isodir/boot/grub")

# Copy the kernel binary and GRUB config to the appropriate directory
add_custom_command(TARGET kernel POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
            "${CMAKE_BINARY_DIR}/kernel"
            "${CMAKE_BINARY_DIR}/isodir/boot/kernel"
    COMMAND ${CMAKE_COMMAND} -E copy
            "${CMAKE_SOURCE_DIR}/src/grub/grub.cfg"
            "${CMAKE_BINARY_DIR}/isodir/boot/grub/grub.cfg")

# Create the ISO image
add_custom_command(TARGET kernel POST_BUILD
    COMMAND grub-mkrescue -o "${CMAKE_BINARY_DIR}/kernel.iso" "${CMAKE_BINARY_DIR}/isodir"
    COMMENT "Creating ISO image...")