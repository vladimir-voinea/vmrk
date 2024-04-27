cmake_minimum_required(VERSION 3.10)

project(vmrk LANGUAGES CXX C)

set(TARGET "x86_64")
set(TARGET_TRIPLET "${TARGET}-elf-none")

enable_language(ASM)

set(SHARED_FLAGS "-ffreestanding -nostdlib -fno-builtin -MMD -mno-red-zone -mcmodel=kernel -fno-pic -fno-pie -no-pie -O2 -g -Wall -Wextra")

set(CMAKE_ASM_COMPILER gcc)
set(CMAKE_ASM_FLAGS "${SHARED_FLAGS} -Wa,--divide")

set(CMAKE_C_COMPILER gcc)
set(CMAKE_CXX_COMPILER g++)

set(CMAKE_CXX_FLAGS "${SHARED_FLAGS} -fno-exceptions -fno-rtti")
set(CMAKE_C_FLAGS "${SHARED_FLAGS}")

set(CMAKE_CXX_STANDARD_LIBRARIES "")
set(CMAKE_C_STANDARD_LIBRARIES "")

add_subdirectory(src)
