add_executable(kernel
    src/kernel.cxx
)

target_link_libraries(kernel PRIVATE boot bootstrap terminal libc)

set_target_properties(kernel PROPERTIES
    LINK_FLAGS "-mcmodel=kernel -fno-builtin -z max-page-size=4096 -Wl,--build-id=none -Wl,-Map=output.map -T ${CMAKE_CURRENT_SOURCE_DIR}/linker/linker.ld"
)
