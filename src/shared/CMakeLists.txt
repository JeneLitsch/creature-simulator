cmake_minimum_required (VERSION 3.13)

add_library(libshared
	LocalConnection.cpp
)

target_link_libraries(libshared
	"pthread"
)

