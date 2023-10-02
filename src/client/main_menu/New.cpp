#include "New.hpp"
#include "Main.hpp"
#include "imgui.h"
#include "client/session/Session.hpp"
#include "ui.hpp"
#include "client/level/configMenu.hpp"

namespace client::main_menu {


	New::New(stx::reference<Main> main)
		: Sub{main} {

		this->set_title("New Simulation");
	}



	void New::update(double dt) {
	}



	void New::ui_content() {
		ui_world(this->preset, this->rng);
		ImGui::NewLine();
		ui_entities(this->preset);
		ImGui::NewLine();
		ui_obstacles(this->preset.obstacles, this->radio_index);

		ImGui::SeparatorText("Initial Config");
		level::ui_config(this->config);

		ImGui::NewLine();
		ImGui::SetWindowFontScale(2);
		if(ImGui::Button("Generate")) {
			this->generate();
		}
		ImGui::SetWindowFontScale(1);

	}



	void New::generate() {
		this->pop();
		this->pop();
		this->push(std::make_unique<session::Session>(this->preset, this->config));
	}



	void New::render(sf::RenderTarget & render_target) {

	}
}