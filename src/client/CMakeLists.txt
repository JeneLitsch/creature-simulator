cmake_minimum_required (VERSION 3.13)

add_library(client
	Client.cpp
)

add_subdirectory(core)
add_subdirectory(edit)
add_subdirectory(file)
add_subdirectory(view)
add_subdirectory(session)
add_subdirectory(main_menu)
add_subdirectory(test)

target_link_libraries(client
	pthread
)

target_link_libraries(client
	sfml-graphics
	sfml-audio
	sfml-network
	sfml-system
	sfml-window
	imgui
)
