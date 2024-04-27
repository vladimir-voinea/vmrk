cmake_minimum_required(VERSION 3.10)

project(vmrk LANGUAGES CXX C)

set(TARGET "i686")
set(TARGET_TRIPLET "${TARGET}-elf-none")

enable_language(ASM)

set(CMAKE_ASM_COMPILER clang++)
set(CMAKE_ASM_FLAGS "-target ${TARGET_TRIPLET}")

set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)

set(CMAKE_CXX_FLAGS "-target ${TARGET_TRIPLET} -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti")
set(CMAKE_C_FLAGS "-target ${TARGET_TRIPLET} -ffreestanding -O2 -Wall -Wextra")

set(CMAKE_CXX_STANDARD_LIBRARIES "")
set(CMAKE_C_STANDARD_LIBRARIES "")

add_subdirectory(src)
