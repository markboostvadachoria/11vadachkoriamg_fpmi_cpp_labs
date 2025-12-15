cmake_minimum_required(VERSION 3.10)
project(TestLab2)

set(CMAKE_CXX_STANDARD 17)

add_executable(lab2_test test/test.cpp src/main.cpp)

find_package(GTest REQUIRED)
target_link_libraries(lab2_test GTest::gtest GTest::gtest_main)
