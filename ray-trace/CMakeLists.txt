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

# Program used to view the rendered image (ImageMagick by default)
set(RAY_TRACE_VIEWER "display" CACHE STRING "Command used to display the rendered PPM")
set(RAY_TRACE_OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/ray-trace.ppm")

# Render and display: cmake --build <build-dir> --target run
# Equivalent to: make && ./ray-trace > ray-trace.ppm && display ray-trace.ppm
# add_custom_target cannot express shell redirection, so generate a wrapper script.
file(GENERATE OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/run.sh" CONTENT
"#!/bin/sh\nexec \"$<TARGET_FILE:ray-trace>\" > \"${RAY_TRACE_OUTPUT}\"\n"
)

add_custom_target(run
	COMMAND sh "${CMAKE_CURRENT_BINARY_DIR}/run.sh"
	COMMAND ${RAY_TRACE_VIEWER} "${RAY_TRACE_OUTPUT}"
	DEPENDS ray-trace
	USES_TERMINAL
	COMMENT "Rendering ${RAY_TRACE_OUTPUT} and displaying it"
)
