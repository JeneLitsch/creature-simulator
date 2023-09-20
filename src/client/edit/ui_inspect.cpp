#include "ui_inspect.hpp"
#include "imgui.h"

namespace client::edit {
	void ui_inspect(sim::Ecs::Entity & entity) {
		ImGui::Begin("Inspector");
		ImGui::Text("Entity #%lu", entity.get_id());

		// Add details here

		ImGui::End();
	}
}