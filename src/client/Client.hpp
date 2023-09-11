#pragma once
#include <SFML/Graphics.hpp>
#include "core/Event.hpp"
#include "core/StateManager.hpp"

namespace client {
	class Client {
	public:
		Client();
		void run();
	private:
		void on_event(const core::Closed & event);
		void on_event(const core::WindowResized & event);
		void on_event(const core::ButtonPressed & event);
		void on_event(auto) {}
        bool showMenu = false;
		sf::RenderWindow window;
		core::StateManager state_manager;
		sf::Clock clock;
		sf::Time then;
		sf::Time now;
	};
}
