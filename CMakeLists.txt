cmake_minimum_required(VERSION 3.15)
project(merge_conflicts_resolver)

set(CMAKE_CXX_STANDARD 14)

include_directories(base)

add_subdirectory(tests)

add_executable(merge_conflicts_resolver
        main.cpp fileHandler.hpp parser.hpp conflicts.hpp parsedCode.hpp resolver.hpp)


