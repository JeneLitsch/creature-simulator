#include "Main.hpp"
#include "New.hpp"
#include "imgui.h"
#include "client/session/Session.hpp"
#include "calc_margin.hpp"

namespace client::main_menu {
	void Main::update(double dt) {
	
	}



	void Main::ui(stx::vector2f window_size) {
		const stx::vector2f margin = calc_margin();
		const stx::vector2f panel_position = margin;
		const stx::vector2f panel_size     = window_size * stx::vector2f{0.25f, 1.f} - 2.f * margin;
        
		ImGui::Begin("Creature Simulator", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
		ImGui::SetWindowPos(panel_position.to<ImVec2>(), 0);
		ImGui::SetWindowSize(panel_size.to<ImVec2>(), 0);
		ImGui::SetWindowFontScale(2);
		if(ImGui::Button("New Simulation", {ImGui::GetContentRegionAvail().x, 0})) {
			for(std::uint64_t i = 0; i < this->sub_menu_count; ++i) {
				this->pop();
			}
			this->push(std::make_unique<New>(*this));
		}
		if(ImGui::Button("Quit", {ImGui::GetContentRegionAvail().x, 0})) {
			this->clear();
		}
        ImGui::End();
	}



	void Main::render(sf::RenderTarget & render_target) {
		
	}
}