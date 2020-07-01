cmake_minimum_required(VERSION 3.15)
project(cpp_lab2)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(cpp_lab2
        main.cpp
        safe_c_array_t.hpp
        safe_long_long_t.cpp safe_long_long_t.hpp)
