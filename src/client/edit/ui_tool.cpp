#include "ui_tool.hpp"
#include "imgui.h"

namespace client::edit {
	stx::optref<Tool> ui_tool(std::vector<Tool> & tools, stx::optref<Tool> current_tool) {
		ImGui::Begin("Tools");

		for(auto & tool : tools) {
			if(ImGui::Button(tool.name.c_str(), {ImGui::GetContentRegionAvail().x, 0})) {
				current_tool = tool;
			}
		}

		if(current_tool) {
			current_tool->ui();
		}
		else {
			ImGui::Text("- None -");
		}

		ImGui::End();

		return current_tool;
	}
}