#include "App.hpp"

namespace core {
	App::App() {
		this->window.create(sf::VideoMode{256,256}, "Creature Simulator");
	}


	
	void App::run() {
		while (this->window.isOpen()) {
			while (auto event = fetch_event(this->window)) {
				std::visit([this] (const auto & e) { this->on_event(e); }, *event);
			}

			this->window.clear(sf::Color::Black);
			this->window.display();
		}
	}



	void App::on_event(const Closed &) {
		this->window.close();
	}
}