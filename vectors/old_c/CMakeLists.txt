cmake_minimum_required(VERSION 3.16)
project(vectors LANGUAGES C)
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_library(vector STATIC vector.c)
target_include_directories(vector PUBLIC vectors)

target_compile_options(vector PUBLIC -O3 -march=native -ffast-math -funroll-loops -Wall -Wextra -Wpedantic -Werror)

target_link_libraries(vector PUBLIC m)
