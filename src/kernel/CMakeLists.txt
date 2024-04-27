add_executable(kernel
    src/kernel.cxx
)

target_link_libraries(kernel ${TARGET}-boot bootstrap terminal libc)

set_target_properties(kernel PROPERTIES
    LINK_FLAGS "-target ${TARGET_TRIPLET} -Wl -T ${CMAKE_CURRENT_SOURCE_DIR}/linker/linker.ld -nostdlib -ffreestanding"
)
