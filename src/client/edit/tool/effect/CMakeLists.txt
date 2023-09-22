cmake_minimum_required (VERSION 3.13)

target_sources(client PRIVATE
	Barrier.cpp
	Erase.cpp
	Inspect.cpp
	Petrify.cpp
	PlaceEmptyCreature.cpp
	PlaceFood.cpp
	PlaceFoodSpawner.cpp
)
