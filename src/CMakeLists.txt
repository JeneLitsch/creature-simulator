cmake_minimum_required (VERSION 3.13)

# add_subdirectory(shared)
add_subdirectory(client)
# add_subdirectory(server)

add_executable(client main_client.cpp)
target_link_libraries(client libclient)
