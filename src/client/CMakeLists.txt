cmake_minimum_required (VERSION 3.13)

add_library(libclient
	Client.cpp
)

add_subdirectory(core)
add_subdirectory(level)
add_subdirectory(session)
add_subdirectory(main_menu)
add_subdirectory(test)

target_link_libraries(libclient
	pthread
)

target_link_libraries(libclient
	sfml-graphics
	sfml-audio
	sfml-network
	sfml-system
	sfml-window
)

target_link_libraries(libclient
	libshared
)
