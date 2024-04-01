cmake_minimum_required(VERSION 2.9)
project(NewPytorch)

# # Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Link runTests with what we want to test and the GTest and pthread library
add_executable(main src/main.cpp src/vector.cpp)
add_executable(runTests tests/test.cpp src/vector.cpp)
target_link_libraries(runTests ${GTEST_LIBRARIES})