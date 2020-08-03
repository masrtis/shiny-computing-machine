add_library(io
    framebuffer.cpp
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
    crt
    io_asm
)

target_link_libraries(io PRIVATE
    kernel_build_options
)