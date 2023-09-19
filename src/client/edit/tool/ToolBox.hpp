#pragma once
#include "stdxx/reference.hxx"
#include "Tool.hpp"
#include "Eraser.hpp"

namespace client::edit {
	struct ToolBox {
		Eraser eraser;

		stx::optref<Tool> current;
	};
}