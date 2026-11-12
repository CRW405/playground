cmake_minimum_required(VERSION 3.25)
project(ray-trace LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

add_executable(ray-trace main.cpp)

target_include_directories(ray-trace PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/../vectors
)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
	target_compile_options(ray-trace PRIVATE
		-O3
		-march=native
		-ffast-math
		-funroll-loops
		-Wall
		-Wextra
		-Wpedantic
		-Werror
	)
endif()
