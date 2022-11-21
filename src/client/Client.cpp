#include "Client.hpp"
#include "test/Test.hpp"
#include "session/HostSession.hpp"
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
		this->state_manager.push(std::make_unique<session::HostSession>());
		this->window.setFramerateLimit(60);
	}



	void Client::run() {
		this->clock.restart();
		this->now = this->clock.getElapsedTime();
		while (this->window.isOpen()) {
			this->state_manager.handle_queue();
			while (auto event = core::fetch_event(this->window)) {
				std::visit([this] (const auto & e) { this->on_event(e); }, *event);
				this->state_manager.events(*event);
			}

			this->then = this->now;
			this->now = this->clock.getElapsedTime();

			const auto dt = (this->now - this->then).asSeconds();
			// std::cout << (1.f / dt) << "\n";

			this->state_manager.update(dt);
			this->window.clear(sf::Color::Black);
			this->state_manager.render(this->window);
			this->window.display();
		}
	}



	void Client::on_event(const core::Closed &) {
		this->window.close();
	}



	void Client::on_event(const core::WindowResized & event) {
		auto view = this->window.getView();
		view.setViewport(calc_view_port(this->window, view));
		this->window.setView(view);
	}
}