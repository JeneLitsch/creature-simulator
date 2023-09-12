#include "Start.hpp"
#include "imgui.h"
#include "client/session/Session.hpp"

namespace client::start {
	void Start::update(double dt) {
        ImGui::Begin("Creature Simulator", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove);
		ImGui::SetWindowPos({64,64}, 0);
		ImGui::SetWindowFontScale(2);
		if(ImGui::Button("START")) {
			this->pop();
			this->push(std::make_unique<session::Session>());
		}
		if(ImGui::Button("QUIT")) {
			this->clear();
		}
        ImGui::End();
	}



	void Start::render(sf::RenderTarget & render_target) {
	}
}