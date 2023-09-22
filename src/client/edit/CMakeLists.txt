cmake_minimum_required (VERSION 3.13)

target_sources(client PRIVATE
	Edit.cpp
	render_neural_network.cpp
	ui_tool.cpp
	ui_inspect.cpp
)


add_subdirectory(tool)