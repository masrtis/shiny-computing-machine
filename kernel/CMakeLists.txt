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

target_link_options(kernel_cxx_build_options INTERFACE
    -nostartfiles
    -nostdlib
)

target_link_libraries(kernel_cxx_build_options INTERFACE
    kernel_c_build_options
)

# Level 0
add_subdirectory(crt)
add_subdirectory(io)

# Level 1
add_subdirectory(debug_log)

# Level 2
add_subdirectory(test)

add_library(kernel
    kmain.cpp
)

target_link_libraries(kernel PUBLIC
    crt_test
    debug_log
    io
)

target_link_libraries(kernel PRIVATE
    kernel_cxx_build_options
)
