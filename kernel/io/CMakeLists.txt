add_library(io
    framebuffer.cpp
    serial.cpp
    stdio.cpp
)

add_library(io_asm
    io.asm
)

target_include_directories(io PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_include_directories(io_asm PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(io PUBLIC
    freestanding
    io_asm
)

target_link_libraries(io PRIVATE
    kernel_cxx_build_options
)
