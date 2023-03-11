cmake_minimum_required(VERSION 3.16)

project(ch18)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    add_compile_options(/utf-8)
endif()

add_executable(
    01-JThreadSample
    Projects/01-JThreadSample/src/main.cpp
)

add_executable(
    02-SourceLocation
    Projects/02-SourceLocation/src/main.cpp
)

add_executable(
    03-Calendar
    Projects/03-Calendar/src/main.cpp
)

add_executable(
    04-Timezone
    Projects/04-Timezone/src/main.cpp
)

add_executable(
    05-SyncStream
    Projects/05-SyncStream/src/main.cpp
)

add_executable(
    06-U8String
    Projects/06-U8String/src/main.cpp
)

add_executable(
    07-WindowsThread
    Projects/07-WindowsThread/src/main.cpp
)
