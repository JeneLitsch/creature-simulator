#include "Client.hpp"
#include "imgui-SFML.h"
#include "imgui.h"
#include "test/Test.hpp"
#include "session/Session.hpp"
#include "main_menu/Main.hpp"
#include "imguiStyle.cpp"
#include <iostream>

namespace client {
	namespace {
		// Keeps aspect ratio and adds black bars if nessesary
		sf::FloatRect calc_view_port(
			const sf::Window & window,
			const sf::View & view){

			const float aspect_ratio_window
				= float(window.getSize().x)
				/ float(window.getSize().y);

			const float aspect_ratio_buffer
				= float(view.getSize().x)
				/ float(view.getSize().y);

			if(aspect_ratio_buffer > aspect_ratio_window){
				const float relative_height = aspect_ratio_window/aspect_ratio_buffer;
				const float offset = (1.f - relative_height) / 2.f;
				return sf::FloatRect(0.f, offset, 1.f, relative_height);
			}
			else {
				const float relative_width = aspect_ratio_buffer/aspect_ratio_window;
				const float offset = (1.f - relative_width) / 2.f;
				return sf::FloatRect(offset, 0.f, relative_width, 1.f);
			}	
		}
	}




	Client::Client() {
		sf::View view{{960/2, 540/2}, {960, 540}};
		this->window.create(sf::VideoMode{960, 540}, "Creature Simulator");
		this->window.setView(view);
		// this->state_manager.push(std::make_unique<session::Session>());
		this->state_manager.push(std::make_unique<main_menu::Main>());
		this->window.setFramerateLimit(60);
		this->window.setVerticalSyncEnabled(true);
        ImGui::SFML::Init(this->window);
        InitImguiStyle();

	}



	void Client::run() {
		this->clock.restart();
		this->now = this->clock.getElapsedTime();
		while (this->window.isOpen()) {
			this->state_manager.handle_queue();
			if(this->state_manager.terminated()) {
				this->on_event(core::Closed{});
				continue;
			}
			while (auto event = core::fetch_event(this->window)) {
				std::visit([this] (const auto & e) { this->on_event(e); }, *event);
				this->state_manager.events(*event);
			}

            ImGui::SFML::Update(this->window, this->now - this->then);
            if (((static_cast<float>(sf::VideoMode::getFullscreenModes()[0].height)) / 1080.0f) > 1.5)
                ImGui::GetFont()->Scale = 2;
			this->then = this->now;
			this->now = this->clock.getElapsedTime();

			const auto dt = (this->now - this->then).asSeconds();
			// std::cout << (1.f / dt) << "\n";

			this->state_manager.update(dt);
			this->state_manager.ui({
				static_cast<float>(this->window.getSize().x),
				static_cast<float>(this->window.getSize().y)
			});
			this->window.clear(sf::Color::Black);
			this->state_manager.render(this->window);
            ImGui::SFML::Render(this->window);
			this->window.display();
		}
        ImGui::SFML::Shutdown();
	}



	void Client::on_event(const core::Closed &) {
		std::cout << "Close window\n";
		this->window.close();
	}



	void Client::on_event(const core::WindowResized & event) {
		auto view = this->window.getView();
		view.setViewport(calc_view_port(this->window, view));
		this->window.setView(view);
	}



	void Client::on_event(const core::MouseMoved & event) {

	}
}
