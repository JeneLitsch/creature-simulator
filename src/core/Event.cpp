#include "Event.hpp"

namespace core {
	namespace {
		Event event_closed(const sf::Event &) {
			return Closed{};
		}
	}


	std::optional<Event> fetch_event(sf::Window & window) {
		sf::Event event;
		if(window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed: return event_closed(event);
			default: return std::nullopt;
			}
		}
		else return std::nullopt;
	}
}