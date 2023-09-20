cmake_minimum_required (VERSION 3.13)

target_sources(libclient PRIVATE
	Edit.cpp
	ui_tool.cpp
	ui_inspect.cpp
)


add_subdirectory(tool)