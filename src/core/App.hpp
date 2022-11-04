#pragma once
#include <SFML/Graphics.hpp>
#include "Event.hpp"

namespace core {
	class App {
	public:
		App();
		void run();
	private:
		void on_event(const Closed & event);
		void on_event(auto) {}
		sf::RenderWindow window;
	};
}