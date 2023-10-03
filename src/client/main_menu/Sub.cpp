#include "Sub.hpp"
#include "Main.hpp"
#include "imgui.h"
#include "calc_margin.hpp"

namespace client::main_menu {
	Sub::Sub(stx::reference<Main> main)
		: main{main} {
		++main->sub_menu_count;
	}



	void Sub::update(double dt) {
	}



	void Sub::ui(stx::vector2f window_size) {
		this->main->ui(window_size);
		
		const stx::vector2f margin = calc_margin();
		const stx::vector2f panel_position = window_size * stx::vector2f{0.25f, 0.f} + margin;
		const stx::vector2f panel_size     = window_size * stx::vector2f{0.75f, 1.f} - 2.f * margin;

		ImGui::Begin(title.c_str(), nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
		ImGui::SetWindowPos(panel_position.to<ImVec2>(), 0);
		ImGui::SetWindowSize(panel_size.to<ImVec2>(), 0);
		this->ui_content();
		ImGui::End();
	}



	void Sub::render(sf::RenderTarget & render_target) {

	}



	void Sub::set_title(std::string str) {
		this->title = str;
	}


	Sub::~Sub() {
		--this->main->sub_menu_count;
	}
}