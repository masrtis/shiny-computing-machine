add_library(crt
    limits.c
    stddef.c
    stdint.c
    string.c
)

target_include_directories(crt PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(crt PRIVATE
    kernel_build_options
)