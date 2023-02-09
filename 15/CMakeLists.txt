cmake_minimum_required(VERSION 3.16)

project(ch14)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    add_compile_options(/utf-8)
endif()

function (add_deps TGT)
    target_include_directories(
        ${TGT}
        PRIVATE
        Projects/logger/include
    )
endfunction()

add_library(
    logging
    Projects/logger/src/logging/formatters/CFormatter.cpp
    Projects/logger/src/logging/formatters/ModernFormatter.cpp
    Projects/logger/src/logging/formatters/StreamFormatter.cpp
)
target_sources(
    logging
    PRIVATE
    Projects/logger/include/logging/Formatter.h
    Projects/logger/include/logging/Handler.h
    Projects/logger/include/logging/Level.h
    Projects/logger/include/logging/Logger.h
    Projects/logger/include/logging/Record.h
    Projects/logger/include/logging/formatters/CFormatter.h
    Projects/logger/include/logging/formatters/ModernFormatter.h
    Projects/logger/include/logging/formatters/StreamFormatter.h
    Projects/logger/include/logging/handlers/DefaultHandler.h
    Projects/logger/include/logging/handlers/FileHandler.h
    Projects/logger/include/logging/handlers/StreamHandler.h
)
add_deps(logging)

add_executable(
    sample
    Projects/sample/src/main.cpp
)
add_deps(sample)
target_link_libraries(sample logging)
