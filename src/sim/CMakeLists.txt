cmake_minimum_required (VERSION 3.13)

add_library(sim
	Simulation.cpp
	export.cpp
	import.cpp
	create.cpp
	generate.cpp
)

add_subdirectory(component)
add_subdirectory(system)

target_link_libraries(sim
	sfml-graphics
	sfml-audio
	sfml-network
	sfml-system
	sfml-window
)