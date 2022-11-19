#include "Event.hpp"

namespace client::core {
	namespace {
		Event event_closed(const sf::Event &) {
			return Closed{};
		}

		Event event_window_resized(const sf::Event & event) {
			return WindowResized{};
		}
	}


	std::optional<Event> fetch_event(sf::Window & window) {
		sf::Event event;
		if(window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed: return event_closed(event);
			case sf::Event::Resized: return event_window_resized(event);
			default: return std::nullopt;
			}
		}
		else return std::nullopt;
	}
}