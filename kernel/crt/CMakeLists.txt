add_library(crt
    string.c
)

target_include_directories(crt PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(crt PRIVATE
    kernel_c_build_options
)
