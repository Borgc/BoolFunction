cmake_minimum_required(VERSION 3.24)
project(BF)

set(CMAKE_CXX_STANDARD 17)

add_library(library.h library.cpp main.cpp)
add_executable(main main.cpp library.cpp library.h)