cmake_minimum_required (VERSION 3.13)

add_library(libshared empty.cpp)
add_subdirectory(imgui)

target_link_libraries(libshared
	"pthread"
)

