cmake_minimum_required(VERSION 3.5)

# Abseil requires C++11
set(CMAKE_CXX_STANDARD 11)

# Process Abseil's CMake build system
add_subdirectory(abseil-cpp)

add_executable(test MapTest.cc SetTest.cc)

# Declare dependency on the absl::strings library
target_link_libraries(test gtest_main gtest pthread)