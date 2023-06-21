cmake_minimum_required (VERSION 3.13)

target_sources(libsim PRIVATE
	emit_pheromones.cpp
	metabolize.cpp
	move.cpp
	read_sensors.cpp
	reproduce.cpp
	spawn_food.cpp
)
