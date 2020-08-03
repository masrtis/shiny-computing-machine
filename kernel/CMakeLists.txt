add_library(kernel_build_options INTERFACE)

target_compile_options(kernel_build_options INTERFACE
    -ffreestanding
    -Wall
    -Wextra
    -Werror
)

add_subdirectory(crt)
add_subdirectory(io)

add_library(kernel
    kmain.cpp
)

target_link_options(kernel PUBLIC
    -nostartfiles
    -nostdlib
)

target_link_libraries(kernel PUBLIC
    io
)

target_link_libraries(kernel PRIVATE
    kernel_build_options
)