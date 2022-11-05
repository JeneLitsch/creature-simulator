#include "App.hpp"
#include "test/Test.hpp"

App::App() {
	this->window.create(sf::VideoMode{256,256}, "Creature Simulator");
	this->state_manager.push(std::make_unique<test::Test>());
}



void App::run() {
	while (this->window.isOpen()) {
		while (auto event = core::fetch_event(this->window)) {
			std::visit([this] (const auto & e) { this->on_event(e); }, *event);
			this->state_manager.events(*event);
		}

		this->state_manager.update(0.0);
		this->state_manager.render(this->window);

		this->window.clear(sf::Color::Black);
		this->window.display();
	}
}



void App::on_event(const core::Closed &) {
	this->window.close();
}