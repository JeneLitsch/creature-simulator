cmake_minimum_required (VERSION 3.8)
project (creature_simulator)
option(BUILD_SHARED_LIBS "Build using shared libraries" OFF)

include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/libs/stdxx)
include_directories(${CMAKE_SOURCE_DIR}/libs/nanocomp)
include_directories(SYSTEM ${CMAKE_SOURCE_DIR}/libs/sfml/include)
include_directories(SYSTEM ${CMAKE_SOURCE_DIR}/libs/imgui)
include_directories(SYSTEM ${CMAKE_SOURCE_DIR}/libs/xoshiro)

# uncomment for windows standalone exe
#set(CMAKE_CXX_STANDARD_LIBRARIES "-static-libgcc -static-libstdc++ -lwsock32 -lws2_32 ${CMAKE_CSS_STANDARD_LIBRARIES}")
#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-Bstatic,--whole-archive -lwinpthread -Wl,--no-whole-archive")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_CXX_STANDARD 20)

add_compile_options(
	# uncomment for windows standalone exe
	#-static 
	#-static-libgcc 
	#-static-libstdc++
	-g
	-O3
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
	-Wno-unused-parameter 
)

add_subdirectory(libs/sfml)
add_subdirectory(libs/imgui)
add_subdirectory(src)


target_compile_options(sfml-graphics PRIVATE -w)
target_compile_options(sfml-system PRIVATE -w)
target_compile_options(sfml-audio PRIVATE -w)
target_compile_options(sfml-network PRIVATE -w)
target_compile_options(sfml-window PRIVATE -w)
target_compile_options(imgui PRIVATE -w)

