cmake_minimum_required(VERSION 3.16)

project(ch14)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    add_compile_options(/utf-8)
endif()

add_executable(
    01-SimpleLog
    Projects/01-SimpleLog/src/main.cpp
)

add_executable(
    02-FormatTo
    Projects/02-FormatTo/src/main.cpp
)

add_executable(
    03-VFormat
    Projects/03-VFormat/src/main.cpp
)

add_executable(
    04-Formatter
    Projects/04-Formatter/src/main.cpp
)
