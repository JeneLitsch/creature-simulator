cmake_minimum_required (VERSION 3.13)

add_subdirectory(client)
add_subdirectory(sim)

add_executable(app main_client.cpp)
target_link_libraries(app client sim imgui)
