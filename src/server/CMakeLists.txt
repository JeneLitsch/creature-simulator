cmake_minimum_required (VERSION 3.13)

add_library(libserver
	emit_pheromones.cpp
	move_randomly.cpp
	read_sensors.cpp
	Server.cpp
	Socket.cpp
)

add_subdirectory(senses)

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