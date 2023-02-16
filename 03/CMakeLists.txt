cmake_minimum_required(VERSION 3.16)

set (TARGET ImageProcessorUniversal)

project(${TARGET})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_custom_target(std_modules ALL
    COMMAND ${CMAKE_COMMAND} -E echo "Building standard library modules"
    COMMAND g++ -fmodules-ts -std=c++20 -c -x c++-system-header iostream string vector map functional cstdint memory

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
    add_compile_options(-fmodules-ts)

	add_executable(
		${TARGET}
		src/command/argument.cpp
		src/command/parser.cpp
		src/command/command.cpp
		src/network/request.cpp 
		src/network/response.cpp
		src/network/connection.cpp
		src/network/server.cpp
		src/network/network.cpp
		src/cache/loader.cpp
		src/cache/cache.cpp
		src/image/processor.cpp
		src/image/image.cpp
		src/app/app.cpp
		src/main.cpp
	)

	if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
		prepare_for_module(${TARGET})
	endif()

elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
	add_executable(
		ImageProcessorUniversal
		src/command/argument.ixx
		src/command/parser.ixx
		src/command/command.ixx
		src/network/request.ixx 
		src/network/response.ixx
		src/network/connection.ixx
		src/network/server.ixx
		src/network/network.ixx
		src/cache/loader.ixx
		src/cache/cache.ixx
		src/image/processor.ixx
		src/image/image.ixx
		src/app/app.ixx
		src/main.cpp
	)
endif()
