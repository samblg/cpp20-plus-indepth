cmake_minimum_required(VERSION 3.16)

project(ch19)

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
    calendar
    Projects/calendar/src/main.cpp
    Projects/calendar/src/Logger.cpp
    Projects/calendar/src/menu/Menu.cpp
    Projects/calendar/src/actions/ShowAction.cpp
    Projects/calendar/src/actions/ExportAction.cpp
    Projects/calendar/src/actions/ExitAction.cpp
    Projects/calendar/src/utils/CalendarUtils.cpp
    Projects/calendar/src/utils/RenderUtils.cpp
    Projects/calendar/src/utils/IoUtils.cpp
    Projects/calendar/include/Logger.h
    Projects/calendar/include/menu/Menu.h
    Projects/calendar/include/actions/ShowAction.h
    Projects/calendar/include/actions/ExportAction.h
    Projects/calendar/include/actions/ExitAction.h
    Projects/calendar/include/utils/CalendarUtils.h
    Projects/calendar/include/utils/RenderUtils.h
    Projects/calendar/include/utils/IoUtils.h
)
target_include_directories(
    calendar
    PRIVATE
    Projects/calendar/include
)
add_deps(calendar)
target_link_libraries(calendar logging)
