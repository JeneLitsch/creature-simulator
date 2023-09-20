#pragma once
#include "stdxx/reference.hxx"
#include "Tool.hpp"

namespace client::edit {
	struct ToolBox {
		std::array<Tool, 3> tools {
			Tool::eraser(),
			Tool::barrier(),
			Tool::place_entity(),
		};

		stx::optref<Tool> current;
	};
}