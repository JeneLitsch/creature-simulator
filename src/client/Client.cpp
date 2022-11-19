#include "Client.hpp"
#include "test/Test.hpp"
#include "session/HostSession.hpp"
#include <iostream>

namespace client {
	Client::Client() {
		this->window.create(sf::VideoMode{256,256}, "Creature Simulator");
		this->state_manager.push(std::make_unique<session::HostSession>());
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

			std::cout << 1.f / (this->now - this->then).asSeconds() << "\n";

			this->state_manager.update(0.0);
			this->state_manager.render(this->window);

			this->window.clear(sf::Color::Black);
			this->window.display();
		}
	}



	void Client::on_event(const core::Closed &) {
		this->window.close();
	}
}