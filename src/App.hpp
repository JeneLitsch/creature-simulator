#pragma once
#include <SFML/Graphics.hpp>
#include "core/Event.hpp"
#include "core/StateManager.hpp"

class App {
public:
	App();
	void run();
private:
	void on_event(const core::Closed & event);
	void on_event(auto) {}
	sf::RenderWindow window;
	core::StateManager state_manager;
	sf::Clock clock;
	sf::Time then;
	sf::Time now;
};