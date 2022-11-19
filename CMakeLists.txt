cmake_minimum_required (VERSION 3.8)
     
project (creature_simulator)

include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${PROJECT_SOURCE_DIR}/libs/stdxx)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_CXX_STANDARD 20)
add_compile_options(
	-O2
	-W 
	-Wall 
	-Wextra 
	-pedantic 
	-Wpedantic 
	-pedantic-errors 
	-Wunused 
	-Wwrite-strings 
	-Wconversion 
	-Wunreachable-code 
	-Wuninitialized 
	-Wold-style-cast 
	-Walloca 
	-Wparentheses 
	-Wno-unknown-pragmas 
)

add_subdirectory(src)