set(KERNEL_EXECUTABLE "${CMAKE_CURRENT_BINARY_DIR}/../kernel/kernel")

# Path to the GRUB configuration
set(GRUB_CFG "${CMAKE_CURRENT_SOURCE_DIR}/../grub/grub.cfg")

# Output directories for the ISO file structure
set(ISO_DIR "${CMAKE_CURRENT_BINARY_DIR}/isodir")
set(BOOT_DIR "${ISO_DIR}/boot")
set(GRUB_DIR "${BOOT_DIR}/grub")

# Create output directory structure
add_custom_target(create_iso ALL
    COMMAND ${CMAKE_COMMAND} -E make_directory "${GRUB_DIR}"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "${KERNEL_EXECUTABLE}" "${BOOT_DIR}/kernel"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "${GRUB_CFG}" "${GRUB_DIR}/grub.cfg"
    COMMAND grub-mkrescue -o "${CMAKE_CURRENT_BINARY_DIR}/kernel.iso" "${ISO_DIR}"
    COMMENT "Creating ISO image..."
)

add_dependencies(create_iso kernel)