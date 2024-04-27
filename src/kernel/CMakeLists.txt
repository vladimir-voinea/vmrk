add_executable(kernel
    kernel.cxx
)

target_link_libraries(kernel ${TARGET}-boot)

set_target_properties(kernel PROPERTIES
    LINK_FLAGS "-target ${TARGET_TRIPLET} -Wl -T ${CMAKE_CURRENT_SOURCE_DIR}/linker/linker.ld -nostdlib -ffreestanding"
)
