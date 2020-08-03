add_library(kernel_c_build_options INTERFACE)

target_compile_options(kernel_c_build_options INTERFACE
    -ffreestanding
    -Wall
    -Wextra
    -Werror
)

add_library(kernel_cxx_build_options INTERFACE)

target_compile_options(kernel_cxx_build_options INTERFACE
    -fno-exceptions
    -fno-rtti
)

target_link_libraries(kernel_cxx_build_options INTERFACE
    kernel_c_build_options
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
    kernel_cxx_build_options
)
