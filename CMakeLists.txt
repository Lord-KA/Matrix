cmake_minimum_required(VERSION 3.18.4)
project(Matrixes)
add_executable(run main.cpp Matrix.hpp Matrix.cpp)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_COMPILER_DEBUG = g++)
set(CMAKE_CXX_FLAGS_DEBUG = "-Wpedantic -Wall -Wextra -Wformat=2 -fsanitize=address,undefined -g")


