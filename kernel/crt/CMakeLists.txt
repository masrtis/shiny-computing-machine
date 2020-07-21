add_library(crt
    stddef.c
    stdint.c
    stdlib.c
)

target_include_directories(crt PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(crt PRIVATE
    kernel_build_options
)