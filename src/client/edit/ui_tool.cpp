#include "ui_tool.hpp"
#include "imgui.h"

namespace client::edit {
	void ui_tool(ToolBox & toolbox) {
		ImGui::Begin("Tools");

		for(auto & tool : toolbox.tools) {
			if(ImGui::Button(tool.name.c_str())) {
				toolbox.current = tool;
			}
		}

		if(toolbox.current) {
			toolbox.current->ui();
		}
		else {
			ImGui::Text("- None -");
		}

		ImGui::End();
	}
}