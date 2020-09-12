add_library(crt_test
    string_test.cpp
)

target_link_libraries(crt_test PUBLIC
    freestanding
    debug_log
)

target_include_directories(crt_test PUBLIC
    .
)
