#include "Edit.hpp"
#include "client/level/Level.hpp"
#include "client/session/Session.hpp"
#include "imgui.h"
#include "sim/create.hpp"
#include "ui_tool.hpp"
#include "ui_inspect.hpp"

namespace client::edit {
	Edit::Edit(stx::reference<level::Level> level) 
		: level{level}
		, session{level->session} {
		
		this->tools.push_back(Tool::eraser());
		this->tools.push_back(Tool::barrier());
		this->tools.push_back(Tool::place_entity());
		this->tools.push_back(Tool::inspector(*this));
	}



	void Edit::ui(stx::vector2f window_size) {
		ImGui::Begin("Edit", nullptr
			, ImGuiWindowFlags_NoBackground
			| ImGuiWindowFlags_NoTitleBar
			| ImGuiWindowFlags_NoResize
			| ImGuiWindowFlags_NoMove
			| ImGuiWindowFlags_NoNavFocus
			| ImGuiWindowFlags_NoBringToFrontOnFocus);


		ImGui::SetWindowSize(window_size.to<ImVec2>());
		ImGui::SetWindowPos({0,0});

		ImGui::SetWindowFontScale(4);
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4{255, 255, 0, 255});

		ImGui::Text("Edit Mode!");

		ImGui::PopStyleColor();
		ImGui::SetWindowFontScale(1);

		ImGui::End();
		this->current_tool = ui_tool(this->tools, this->current_tool);
		
		if(auto * entity = session->get_sim().ecs.get_if(this->inspected_id)) {
			ui_inspect(*entity);
		}
		else {
			this->inspected_id = 0;
		}
		
		this->level->ui_config();
	}



	void Edit::update(double dt) {
		this->level->update_camera(dt);

		if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
			if(this->current_tool) {
				this->current_tool->draw(session->get_sim(), this->cursor_position);
			}
		}
	}


	
	void Edit::render(sf::RenderTarget & render_target) {
		this->level->render(render_target);

		auto old_view = render_target.getView();
		render_target.setView(level->get_camera());
		if(this->current_tool) {
			this->current_tool->render(render_target, this->cursor_position);
		}
		render_target.setView(old_view);
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



	void Edit::inspect(std::uint64_t id) {
		this->inspected_id = id;
	}
}