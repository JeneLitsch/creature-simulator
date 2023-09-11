cmake_minimum_required (VERSION 3.13)

add_library(libshared )
add_subdirectory(imgui)

target_link_libraries(libshared
	"pthread"
)

target_link_libraries(libshared
	sfml-graphics
	sfml-audio
	sfml-network
	sfml-system
	sfml-window
)
