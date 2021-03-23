cmake_minimum_required(VERSION 3.17)
project(large_number_arithmetic)

set(CMAKE_CXX_STANDARD 11)

add_executable(large_number_arithmetic main.cpp big_num.h big_num.cpp operator_arithmetic.cpp operator_comparison.cpp operator_iostream.cpp)