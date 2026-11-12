cmake_minimum_required(VERSION 3.16)
project(vectors LANGUAGES C)
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_library(ray-trace STATIC main.c)
target_include_directories(ray-trace PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../vectors)

target_compile_options(ray-trace PUBLIC -O3 -march=native -ffast-math -funroll-loops -Wall -Wextra -Wpedantic -Werror)
