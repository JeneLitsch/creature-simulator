cmake_minimum_required (VERSION 3.13)

add_library(libserver
	Server.cpp
)

target_link_libraries(libserver
	"pthread"
)