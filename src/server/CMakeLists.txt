cmake_minimum_required (VERSION 3.13)

add_library(libserver
	Simulation.cpp
	disperse_pheromones.cpp
)

add_subdirectory(component)
# add_subdirectory(senses)
add_subdirectory(system)

target_link_libraries(libserver
	"pthread"
)

target_link_libraries(libserver
	sfml-graphics
	sfml-audio
	sfml-network
	sfml-system
	sfml-window
)

target_link_libraries(libserver
	libshared
)