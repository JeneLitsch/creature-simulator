#include "Edit.hpp"
#include "Level.hpp"
#include "client/session/Session.hpp"
#include "imgui.h"
#include "configMenu.hpp"
#include "sim/create.hpp"
#include "render.hpp"

namespace client::level {
	Edit::Edit(stx::reference<Level> level) 
		: level{level}
		, session{level->session} {}



	void Edit::ui(stx::vector2f window_size) {
		ImGui::Begin("Edit", nullptr
			, ImGuiWindowFlags_NoBackground
			| ImGuiWindowFlags_NoTitleBar
			| ImGuiWindowFlags_NoResize
			| ImGuiWindowFlags_NoMove);


		ImGui::SetWindowSize(window_size.to<ImVec2>());
		ImGui::SetWindowPos({0,0});

		ImGui::SetWindowFontScale(4);
		ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 255, 0, 255));

		ImGui::Text("Edit Mode!");

		ImGui::PopStyleColor();
		ImGui::SetWindowFontScale(1);

		ImGui::End();
		this->level->ui_config();
	}



	void Edit::update(double dt) {
		this->level->update_camera(dt);

		if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
			auto & ecs = this->session->get_sim().ecs;
			auto & grid = this->session->get_sim().grid;
			if(grid.in_range(this->cursor_position) && grid[this->cursor_position] == 0) {
				sim::create_barrier(ecs, stx::vector2i{this->cursor_position}, grid);
			}
		}

		if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)) {
			auto & ecs = this->session->get_sim().ecs;
			auto & grid = this->session->get_sim().grid;
			if(grid.in_range(this->cursor_position)) {
				const std::uint64_t id = grid[this->cursor_position];
				if(auto * entity = ecs.get_if(id)) {
					ecs.get(id).mark_delete();
					grid[this->cursor_position] = 0;
					ecs.clean_up();
				}
			}
		}
	}


	
	void Edit::render(sf::RenderTarget & render_target) {
		this->level->render(render_target);
		render_cursor(render_target, this->cursor_position);
	}



	void Edit::init() {

	}



	void Edit::on_event(const core::MouseMoved & event)  {
		auto x = event.window->mapPixelToCoords(event.position.to<sf::Vector2i>(), this->level->get_camera());
		this->cursor_position = stx::position2i{stx::floor(stx::position2f::from(x))};
	}


	void Edit::on_event(const core::KeyPressed& event) {
		if(event.code == sf::Keyboard::Space) {
			this->pop();
		}
    }



	void use_tool() {

	}
}