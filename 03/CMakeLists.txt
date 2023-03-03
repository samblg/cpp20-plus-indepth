cmake_minimum_required(VERSION 3.16)

set (TARGET ImageProcessorUniversal)

project(${TARGET})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

function (prepare_for_module TGT)
    target_compile_options(${TGT} PUBLIC -fmodules-ts)
    set_property(TARGET ${TGT} PROPERTY CXX_STANDARD 20)
    set_property(TARGET ${TGT} PROPERTY CXX_EXTENSIONS OFF)
    if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        add_custom_target(std_modules ALL
            COMMAND ${CMAKE_COMMAND} -E echo "Building standard library modules"
            COMMAND g++ -fmodules-ts -std=c++20 -c -x c++-system-header iostream string vector map functional cstdint memory
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        )

        add_dependencies(${TGT} std_modules)
    endif()
endfunction()

set (MODULE_EXT cpp)
if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set (MODULE_EXT ixx)
endif()

add_executable(
    ${TARGET}
        src/command/argument.${MODULE_EXT}
        src/command/parser.${MODULE_EXT}
        src/command/command.${MODULE_EXT}
        src/network/request.${MODULE_EXT} 
        src/network/response.${MODULE_EXT}
        src/network/connection.${MODULE_EXT}
        src/network/server.${MODULE_EXT}
        src/network/network.${MODULE_EXT}
        src/cache/loader.${MODULE_EXT}
        src/cache/cache.${MODULE_EXT}
        src/image/processor.${MODULE_EXT}
        src/image/image.${MODULE_EXT}
        src/app/app.${MODULE_EXT}
        src/main.cpp
    )

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    prepare_for_module(${TARGET})
endif()
