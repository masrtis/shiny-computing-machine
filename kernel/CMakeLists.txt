add_library(kernel_build_options INTERFACE)

target_compile_options(kernel_build_options INTERFACE
    -m32
    -fno-builtin
    -fno-stack-protector
    -nostdinc
    -Wall
    -Wextra
    -Werror
)

add_subdirectory(crt)
add_subdirectory(io)

add_library(kernel
    kmain.c
)

target_link_options(kernel PUBLIC
    -melf_i386
    -nostartfiles
    -nodefaultlibs
    -nostdlib
)

target_link_libraries(kernel PUBLIC
    io
)

target_link_libraries(kernel PRIVATE
    kernel_build_options
)