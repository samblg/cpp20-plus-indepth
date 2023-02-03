cmake_minimum_required(VERSION 3.16)

project(ch11)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    add_compile_options(/utf-8)
endif()

add_executable(
    01-STLSample
    Projects/01-STLSample/src/main.cpp
)

add_executable(
    02-RangesSample
    Projects/02-RangesSample/src/main.cpp
)

add_executable(
    03-RangesIteratorSample
    Projects/03-RangesIteratorSample/src/main.cpp
)

add_executable(
    04-RangesSizeSample
    Projects/04-RangesSizeSample/src/main.cpp
)

add_executable(
    05-RangesDataSample
    Projects/05-RangesDataSample/src/main.cpp
)

add_executable(
    06-RangesDanglingFailed
    Projects/06-RangesDanglingFailed/src/main.cpp
)

add_executable(
    07-RangesDanglingCheck
    Projects/07-RangesDanglingCheck/src/main.cpp
)

add_executable(
    08-ViewBasic
    Projects/08-ViewBasic/src/main.cpp
)

add_executable(
    09-ArrayView
    Projects/09-ArrayView/src/main.cpp
)

add_executable(
    10-FactorySample
    Projects/10-FactorySample/src/main.cpp
)

add_executable(
    11-AdaptorSample
    Projects/11-AdaptorSample/src/main.cpp
)

add_executable(
    12-STLRandom
    Projects/12-STLRandom/src/main.cpp
)

add_executable(
    13-PipelineSample
    Projects/13-PipelineSample/src/main.cpp
)
