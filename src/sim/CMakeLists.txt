cmake_minimum_required (VERSION 3.13)

add_library(libsim
	Simulation.cpp
	disperse_pheromones.cpp
	export.cxx
	create.cpp
)

add_subdirectory(component)
add_subdirectory(senses)
add_subdirectory(system)

target_link_libraries(libsim
	"pthread"
)

target_link_libraries(libsim
	sfml-graphics
	sfml-audio
	sfml-network
	sfml-system
	sfml-window
)

target_link_libraries(libsim
	libshared
)