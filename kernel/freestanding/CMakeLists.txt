add_library(freestanding
    string.c
)

target_include_directories(freestanding PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(freestanding PRIVATE
    kernel_c_build_options
)
