add_library(debug_log
    logOptions.cpp
    logToDisplay.cpp
)

target_link_libraries(debug_log PUBLIC
    freestanding
    io
)

target_include_directories(debug_log PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(debug_log PRIVATE
    kernel_cxx_build_options
)
