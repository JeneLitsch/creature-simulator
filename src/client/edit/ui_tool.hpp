#pragma once
#include <vector>
#include "stdxx/reference.hxx"
#include "tool/Tool.hpp"

namespace client::edit {
	stx::optref<Tool> ui_tool(std::vector<Tool> & tools, stx::optref<Tool>);
} 