execute_process(COMMAND "${CMAKE_C_COMPILER}" -print-file-name=crtbegin.o OUTPUT_VARIABLE crtBeginObj OUTPUT_STRIP_TRAILING_WHITESPACE)
execute_process(COMMAND "${CMAKE_C_COMPILER}" -print-file-name=crtend.o OUTPUT_VARIABLE crtEndObj OUTPUT_STRIP_TRAILING_WHITESPACE)

message("crtbegin.o path: ${crtBeginObj}")
message("crtend.o path: ${crtEndObj}")

add_library(crtInitWrapper OBJECT
    crti.asm
    crtn.asm
)

# According to the answers on https://stackoverflow.com/questions/48296061/ there is no way to remove this hardcoding without
# generating either a script at build time or resorting to combinations of creating static libraries and then unpacking the
# library back into distinct object files. May explore these options in the future but for now hardcode the binary paths
set(crtInitWrapperBinaryDir "${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/crtInitWrapper.dir")
message("CRT initialization wrapper binary directory: ${crtInitWrapperBinaryDir}")

set(crtInitWrapperInitObjects "${crtInitWrapperBinaryDir}/crti.asm.o")
message("CRT initialization wrapper initialization objects: ${crtInitWrapperInitObjects}")

set(crtInitWrapperFiniObjects "${crtInitWrapperBinaryDir}/crtn.asm.o")
message("CRT initialization wrapper finalization objects: ${crtInitWrapperFiniObjects}")

message("C++ compiler path: ${CMAKE_CXX_COMPILER}")

set(CMAKE_CXX_LINK_EXECUTABLE
    "$ENV{HOME}/opt/cross/bin/i686-elf-g++ ${CMAKE_CXX_FLAGS} <LINK_FLAGS> -o <TARGET> <OBJECTS> ${crtInitWrapperInitObjects} ${crtBeginObj} <LINK_LIBRARIES> ${crtEndObj} ${crtInitWrapperFiniObjects} -lgcc")

add_executable(kernel.elf
    loader.asm
)

add_dependencies(kernel.elf
    crtInitWrapper
)

target_link_options(kernel.elf PUBLIC
    "-T${CMAKE_CURRENT_SOURCE_DIR}/link.ld"
)

target_link_libraries(kernel.elf PUBLIC
    kernel
)
