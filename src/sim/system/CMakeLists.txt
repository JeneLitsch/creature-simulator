cmake_minimum_required (VERSION 3.13)

target_sources(sim PRIVATE
	metabolize.cpp
	move.cpp
	reproduce.cpp
	spawn_food.cpp
	check_death.cpp
	eval_neural_net.cpp
	share_food.cpp
)
