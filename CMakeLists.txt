cmake_minimum_required(VERSION 2.9)
project(NewPytorch)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(main src/main.cpp src/vector.cpp)
target_compile_options(main PRIVATE -g)
add_executable(runTests tests/test.cpp src/vector.cpp)
target_link_libraries(runTests ${GTEST_LIBRARIES})