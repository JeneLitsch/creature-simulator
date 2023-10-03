#include "Return.hpp"
#include "imgui.h"
#include "client/main_menu/Main.hpp"

namespace client::view {
	void Return::update(double dt) {

	}



	void Return::ui(stx::vector2f window_size) {
		ImGui::Begin("Edit", nullptr
			, ImGuiWindowFlags_NoBackground
			| ImGuiWindowFlags_NoTitleBar
			| ImGuiWindowFlags_NoResize
			| ImGuiWindowFlags_NoMove
			| ImGuiWindowFlags_NoNavFocus
			| ImGuiWindowFlags_NoBringToFrontOnFocus);

		ImGui::SetWindowSize({0,0});
		ImGui::SetWindowPos({64,64});

		ImGui::SetWindowFontScale(4);

		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4{255, 0, 0, 255});

		ImGui::Text("Are you sure you want to return to the Main Menu?");
		ImGui::Text("Any unsaved simulation progress will be lost!");

		ImGui::NewLine();

		if(ImGui::Button("Return to Main Menu.")) {
			this->pop();
			this->pop();
			this->pop();
			this->push(std::make_unique<main_menu::Main>());
		}

		if(ImGui::Button("Continue Simuation.")) {
			this->pop();
		}

		ImGui::PopStyleColor();
		ImGui::SetWindowFontScale(1);

		ImGui::End();
	}



	void Return::render(sf::RenderTarget & render_target) {
		this->view->render(render_target);
	}



	void Return::init() {

	}



	void Return::on_event(const core::KeyPressed & event) {
		if(event.code == sf::Keyboard::Escape) {
			this->pop();
		}
	}
}