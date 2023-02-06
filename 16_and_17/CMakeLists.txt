cmake_minimum_required(VERSION 3.16)

project(ch12)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    add_compile_options(/utf-8)
endif()

add_executable(
    01-OldBit
    Projects/01-OldBit/src/main.cpp
)

add_executable(
    02-EndianProcess
    Projects/02-EndianProcess/src/main.cpp
)

add_executable(
    03-BitCast
    Projects/03-BitCast/src/main.cpp
)

add_executable(
    04-BitRotating
    Projects/04-BitRotating/src/main.cpp
)

add_executable(
    05-OtherBit
    Projects/05-OtherBit/src/main.cpp
)

add_executable(
    06-DataStream
    Projects/06-DataStream/src/main.cpp
    Projects/06-DataStream/src/data.cpp
    Projects/06-DataStream/src/ca/IoUtils.cpp
    Projects/06-DataStream/src/ca/TimeUtils.cpp
    Projects/06-DataStream/src/ca/algorithms/FunctionalAlgorithm.cpp
    Projects/06-DataStream/src/ca/algorithms/ProcedureAlgorithm.cpp
    Projects/06-DataStream/src/ca/algorithms/RangesAlgorithm.cpp
    Projects/06-DataStream/src/ca/SerializeUtils.cpp
    Projects/06-DataStream/include/data.h
    Projects/06-DataStream/include/ca/IoUtils.h
    Projects/06-DataStream/include/ca/RangeUtils.h
    Projects/06-DataStream/include/ca/TimeUtils.h
    Projects/06-DataStream/include/ca/Types.h
    Projects/06-DataStream/include/ca/BitCompact.h
    Projects/06-DataStream/include/ca/BitUtils.h
    Projects/06-DataStream/include/ca/SerializeUtils.h
    Projects/06-DataStream/include/ca/algorithms/FunctionalAlgorithm.h
    Projects/06-DataStream/include/ca/algorithms/ProcedureAlgorithm.h
    Projects/06-DataStream/include/ca/algorithms/RangesAlgorithm.h
)
target_include_directories(
    06-DataStream
    PRIVATE
    Projects/06-DataStream/include
)
