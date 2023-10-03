#include "Edit.hpp"
#include "client/view/View.hpp"
#include "client/session/Session.hpp"
#include "imgui.h"
#include "sim/create.hpp"
#include "ui_tool.hpp"
#include "ui_inspect.hpp"
#include "render_neural_network.hpp"

namespace client::edit {
	Edit::Edit(stx::reference<view::View> view) 
		: view{view}
		, session{view->session} {
		
		this->tools.push_back(Tool::eraser());
		this->tools.push_back(Tool::barrier());
		this->tools.push_back(Tool::place_empty_creature());
		this->tools.push_back(Tool::place_food());
		this->tools.push_back(Tool::place_food_spawner());
		this->tools.push_back(Tool::inspector(*this));
		this->tools.push_back(Tool::medusa());

		this->neural_network_graph.create(4096,2048);
	}



	void Edit::ui(stx::vector2f window_size) {
		ImGui::Begin("Edit", nullptr
			, ImGuiWindowFlags_NoBackground
			| ImGuiWindowFlags_NoTitleBar
			| ImGuiWindowFlags_NoResize
			| ImGuiWindowFlags_NoMove
			| ImGuiWindowFlags_NoNavFocus
			| ImGuiWindowFlags_NoBringToFrontOnFocus);


		ImGui::SetWindowSize({0,0});
		ImGui::SetWindowPos({0,0});

		ImGui::SetWindowFontScale(4);
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4{255, 255, 0, 255});

		ImGui::Text("Edit Mode!");

		ImGui::PopStyleColor();
		ImGui::SetWindowFontScale(1);

		ImGui::End();
		this->current_tool = ui_tool(this->tools, this->current_tool);
		
		if(auto * entity = session->get_sim().ecs.get_if(this->inspected_id)) {
			this->neural_network_graph.clear(sf::Color::Black);
			if(auto * nn = entity->get_if<sim::NeuralNetwork>()) {
				render_neural_network(*nn,neural_network_graph, session->get_sim().config.neural_net);
			}
			neural_network_graph.display();
			ui_inspect(*entity, this->neural_network_graph);
		}
		else {
			this->inspected_id = 0;
		}
		
		this->view->ui_config();
	}



	void Edit::update(double dt) {
		this->view->update_camera(dt);

		if(this->current_tool && this->is_drawing) {
			this->current_tool->draw(session->get_sim(), this->cursor_position);
		}
	}


	
	void Edit::render(sf::RenderTarget & render_target) {
		this->view->render(render_target);

		auto old_view = render_target.getView();
		render_target.setView(view->get_camera());
		if(this->current_tool) {
			this->current_tool->render(render_target, this->cursor_position);
		}
		render_target.setView(old_view);
	}



	void Edit::init() {

	}



	void Edit::on_event(const core::MouseMoved & event)  {
		auto x = event.window->mapPixelToCoords(event.position.to<sf::Vector2i>(), this->view->get_camera());
		this->cursor_position = stx::position2i{stx::floor(stx::position2f::from(x))};
	}



	void Edit::on_event(const core::KeyPressed& event) {
		if(event.code == sf::Keyboard::Space) {
			this->pop();
		}
    }



	void Edit::on_event(const core::MouseButtonPressed & event) {
		if(event.button == sf::Mouse::Button::Left) {
			this->is_drawing = true;
		}
	}



	void Edit::on_event(const core::MouseButtonReleased & event) {
		if(event.button == sf::Mouse::Button::Left) {
			this->is_drawing = false; 
		}
	}



	void Edit::inspect(std::uint64_t id) {
		this->inspected_id = id;
	}
}