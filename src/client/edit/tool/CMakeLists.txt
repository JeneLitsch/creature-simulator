cmake_minimum_required (VERSION 3.13)

target_sources(client PRIVATE
	Tool.cpp
)

add_subdirectory(effect)
add_subdirectory(shape)