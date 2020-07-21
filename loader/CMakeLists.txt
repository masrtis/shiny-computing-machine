# Make sure that CMake does not try to link to standard libraries implicitly
set(CMAKE_C_IMPLICIT_LINK_LIBRARIES "")
set(CMAKE_C_IMPLICIT_LINK_DIRECTORIES "")

set(CMAKE_ASM_NASM_IMPLICIT_LINK_LIBRARIES "")
set(CMAKE_ASM_NASM_IMPLICIT_LINK_DIRECTORIES "")

add_executable(kernel.elf
    loader.asm
)

target_compile_options(kernel.elf PUBLIC
    -f elf32
)

target_link_options(kernel.elf PUBLIC
    "-T${CMAKE_CURRENT_SOURCE_DIR}/link.ld"
    -melf_i386
)

target_link_libraries(kernel.elf PUBLIC
    kernel
)

set_target_properties(kernel.elf PROPERTIES LINKER_LANGUAGE ASM_NASM)