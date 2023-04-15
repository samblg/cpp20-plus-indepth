cmake_minimum_required(VERSION 3.16)

set (TARGET 02-BasicFileSystem)

project(${TARGET})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CXX_SOURCE_DIR ${PROJECT_SOURCE_DIR}/src)

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    add_compile_options(/utf-8)
endif()

add_executable(
    ${TARGET}
    src/main.cpp
)
