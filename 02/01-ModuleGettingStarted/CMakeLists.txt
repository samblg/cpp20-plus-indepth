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

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
	add_executable(
        01-ModuleGettingStarted
        src/helloworld.cpp
        src/main.cpp
	)

    prepare_for_module(01-ModuleGettingStarted)

elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
	add_executable(
		01-ModuleGettingStarted
        src/helloworld.ixx
        src/main.cpp
	)
endif()
