project(Tests)

project(calendars_tests)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
include_directories(../)

add_executable(tests test.cpp conflicts.cpp)

target_link_libraries(tests GTest::GTest GTest::Main)
