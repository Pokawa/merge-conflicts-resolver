cmake_minimum_required(VERSION 3.15)
project(merge_conflicts_resolver)

set(CMAKE_CXX_STANDARD 14)

include_directories(base)
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

add_subdirectory(tests)

add_executable(mcr
        main.cpp fileHandler.hpp parser.hpp conflicts.hpp parsedCode.hpp resolver.hpp coloredString.hpp printHandler.hpp mergeAid.hpp frontend.hpp backend.hpp)

target_link_libraries(mcr ${CURSES_LIBRARIES})


