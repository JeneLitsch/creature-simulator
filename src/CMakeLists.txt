cmake_minimum_required (VERSION 3.8)

add_executable(app main.cpp App.cpp)
add_subdirectory(core)
add_subdirectory(test)
target_link_libraries(app core test)
target_link_libraries(app "pthread" "sfml-graphics" "sfml-audio" "sfml-network" "sfml-system" "sfml-window")