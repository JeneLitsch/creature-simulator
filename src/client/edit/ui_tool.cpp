#include "ui_tool.hpp"
#include "imgui.h"

namespace client::edit {
	void ui_tool(ToolBox & toolbox) {
		ImGui::Begin("Tools");

		if(ImGui::Button("Eraser")) {
			toolbox.current = toolbox.eraser;
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