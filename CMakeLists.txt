cmake_minimum_required (VERSION 3.8)
project (creature_simulator)
option(BUILD_SHARED_LIBS "Build using shared libraries" OFF)

include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/libs/stdxx)
include_directories(${CMAKE_SOURCE_DIR}/libs/nanocomp)
include_directories(SYSTEM ${CMAKE_SOURCE_DIR}/libs/sfml/include)
include_directories(${CMAKE_SOURCE_DIR}/src/shared/imgui)


set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_CXX_STANDARD 20)

add_compile_options(
	-W 
	-g 
	-Wall 
	-Wextra 
	-pedantic 
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

add_subdirectory(libs/sfml)
add_subdirectory(src)


target_compile_options(sfml-graphics PRIVATE -w)
target_compile_options(sfml-system PRIVATE -w)
target_compile_options(sfml-audio PRIVATE -w)
target_compile_options(sfml-network PRIVATE -w)

