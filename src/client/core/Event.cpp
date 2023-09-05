#include "Event.hpp"
#include "imgui-SFML.h"

namespace client::core {
	namespace {
		Event event_closed(const sf::Event &) {
			return Closed{};
		}

		Event event_window_resized(const sf::Event & event) {
			return WindowResized{};
		}

		Event event_button_pressed(const sf::Event & event) {
			return ButtonPressed{
                .code =  event.key.code,
                .alt =  event.key.alt,
                .control = event.key.control,
                .shift = event.key.shift,
                .system = event.key.system
            };
		}
	}


	std::optional<Event> fetch_event(sf::Window & window) {
		sf::Event event;
		while(window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(event);
			switch (event.type) {
			case sf::Event::Closed: return event_closed(event);
			case sf::Event::Resized: return event_window_resized(event);
			case sf::Event::KeyPressed: return event_button_pressed(event);
			}
		}
		return std::nullopt;
	}
}
