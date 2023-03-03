cmake_minimum_required(VERSION 3.16)

set (TARGET NumCpp)

project(${TARGET})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CXX_SOURCE_DIR ${PROJECT_SOURCE_DIR}/src)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        add_custom_target(std_modules ALL
            COMMAND ${CMAKE_COMMAND} -E echo "Building standard library modules"
            COMMAND g++ -fmodules-ts -std=c++20 -c -x c++-system-header iostream cstdint concepts type_traits vector initializer_list tuple cstring memory algorithm stdexcept array
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        )

        add_dependencies(${TGT} std_modules)
endif()

function (prepare_for_module TGT)
    target_compile_options(${TGT} PUBLIC -fmodules-ts)
    set_property(TARGET ${TGT} PROPERTY CXX_STANDARD 20)
    set_property(TARGET ${TGT} PROPERTY CXX_EXTENSIONS OFF)
    if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        add_dependencies(${TGT} std_modules)
    endif()
endfunction()

set (MODULE_EXT cpp)
if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set (MODULE_EXT ixx)
endif()

add_executable(
    ${TARGET}
    src/numcpp/concepts.${MODULE_EXT}
    src/numcpp/types.${MODULE_EXT}
    src/numcpp/utils.${MODULE_EXT}
    src/numcpp/array_view.${MODULE_EXT}
    src/numcpp/array.${MODULE_EXT}
    src/numcpp/creation.${MODULE_EXT}
    src/numcpp/algorithm/basic.${MODULE_EXT}
    src/numcpp/algorithm/universal.${MODULE_EXT}
    src/numcpp/algorithm/aggregate.${MODULE_EXT}
    src/numcpp/algorithm/algorithm.${MODULE_EXT}
    src/numcpp/numcpp.${MODULE_EXT}
    src/main.cpp
)

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    prepare_for_module(${TARGET})
endif()
