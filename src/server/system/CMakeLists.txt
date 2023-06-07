cmake_minimum_required (VERSION 3.13)

target_sources(libserver PRIVATE
	emit_pheromones.cpp
	metabolize.cpp
	read_sensors.cpp
	reproduce.cpp
)
