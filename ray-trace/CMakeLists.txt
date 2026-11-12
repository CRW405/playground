cmake_minimum_required(VERSION 3.16)
project(ray-trace LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

add_library(ray-trace STATIC main.cpp)
target_include_directories(ray-trace PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../vectors)

target_compile_options(ray-trace PUBLIC -O3 -march=native -ffast-math -funroll-loops -Wall -Wextra -Werror)
