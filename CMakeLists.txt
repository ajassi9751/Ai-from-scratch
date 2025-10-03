cmake_minimum_required(VERSION 3.16)
project(aifs)

set(CMAKE_C_COMPILER="/usr/bin/clang")
set(CMAKE_CXX_COMPILER="/usr/bin/clang++")

add_executable(main src/main.cpp)
