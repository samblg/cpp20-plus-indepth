cmake_minimum_required(VERSION 3.16)

project(ch02)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_custom_target(std_modules ALL
    COMMAND ${CMAKE_COMMAND} -E echo "Building standard library modules"
    COMMAND g++ -fmodules-ts -std=c++20 -c -x c++-system-header iostream cstdint
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)

function (prepare_for_module TGT)
    target_compile_options(${TGT} PUBLIC -fmodules-ts)
    set_property(TARGET ${TGT} PROPERTY CXX_STANDARD 20)
    set_property(TARGET ${TGT} PROPERTY CXX_EXTENSIONS OFF)
	if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        add_dependencies(${TGT} std_modules)
	endif()
endfunction()

set (TARGET 04-GlobalModuleFragment)
set (MODULE_EXT cpp)

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set (MODULE_EXT ixx)
endif()

add_executable(
    ${TARGET}
    src/helloworld.${MODULE_EXT}
    src/main.cpp
)
target_include_directories(
    ${TARGET}
    PRIVATE
    src
)
target_sources(
    ${TARGET}
    PRIVATE
    src/h2.h
)

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    prepare_for_module(${TARGET})
endif()