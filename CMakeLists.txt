cmake_minimum_required(VERSION 3.13 FATAL_ERROR)

# Set up NASM to build 32 bit elf format and use ld for linking
# This should be done before enabling ASM_NASM with project() to ensure CMake does not detect the pointer size as 64 bit on 64 bit OSes
set(CMAKE_ASM_NASM_OBJECT_FORMAT elf)
set(CMAKE_ASM_NASM_LINK_EXECUTABLE "$ENV{HOME}/opt/cross/bin/i686-elf-ld <FLAGS> <CMAKE_ASM_NASM_LINK_FLAGS> <LINK_FLAGS> <OBJECTS> -o <TARGET> <LINK_LIBRARIES>")

set(CMAKE_C_COMPILER $ENV{HOME}/opt/cross/bin/i686-elf-gcc)
set(CMAKE_C_FLAGS "-ffreestanding -nostdlib -nostartfiles")
set(CMAKE_CXX_COMPILER $ENV{HOME}/opt/cross/bin/i686-elf-g++)
set(CMAKE_CXX_FLAGS "-ffreestanding -nostdlib -nostartfiles")

project(os C CXX ASM_NASM)

add_subdirectory(kernel)
add_subdirectory(loader)

add_custom_target(os.iso
    COMMAND cp ${CMAKE_CURRENT_BINARY_DIR}/loader/kernel.elf ${CMAKE_CURRENT_SOURCE_DIR}/iso/boot/kernel.elf && genisoimage -R -b boot/grub/stage2_eltorito -no-emul-boot -boot-load-size 4 -A os -input-charset utf8 -quiet -boot-info-table -o os.iso ${CMAKE_CURRENT_SOURCE_DIR}/iso
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    DEPENDS kernel.elf
)

add_custom_target(run
    COMMAND bochs -f bochsrc.txt -q
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    DEPENDS os.iso
)