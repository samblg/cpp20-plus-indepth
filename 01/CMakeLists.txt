cmake_minimum_required(VERSION 3.16)

project(ch01)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(
    MyAppV1
    src/v1/a.cpp
    src/v1/b.cpp
)

add_executable(
    MyAppV2
    src/v2/a.cpp
    src/v2/b.cpp
)
target_include_directories(
    MyAppV2
    PRIVATE
    src/v2
)
target_sources(
    MyAppV2
    PRIVATE
    src/v2/b.h
)

add_executable(
    MyAppV3
    src/v3/a.cpp
    src/v3/b.cpp
)
target_include_directories(
    MyAppV3
    PRIVATE
    src/v3
)
target_sources(
    MyAppV3
    PRIVATE
    src/v3/b.h
)
