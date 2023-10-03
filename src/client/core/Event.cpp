#include "Event.hpp"
#include "imgui-SFML.h"
#include "imgui.h"

namespace client::core {
	namespace {
		Event event_closed(const sf::Event &) {
			return Closed{};
		}

		Event event_window_resized(const sf::Event & event) {
			return WindowResized{};
		}

		Event event_button_pressed(const sf::Event & event) {
			return KeyPressed{
                .code =  event.key.code,
                .alt =  event.key.alt,
                .control = event.key.control,
                .shift = event.key.shift,
                .system = event.key.system
            };
		}

		Event event_mouse_move(const sf::Event & event, sf::RenderWindow & window) {
			return MouseMoved {
				.position = {event.mouseMove.x,event.mouseMove.y},
				.window = &window,
			};
		}

		Event event_mouse_button_pressed(const sf::Event & event) {
			return MouseButtonPressed {
				.button = event.mouseButton.button,
			};
		}

		Event event_mouse_button_released(const sf::Event & event) {
			return MouseButtonReleased {
				.button = event.mouseButton.button,
			};
		}
	}


	std::optional<Event> fetch_event(sf::RenderWindow & window) {
		sf::Event event;
		while(window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(event);
			if(event.type == sf::Event::Closed)  return event_closed(event);
			if(event.type == sf::Event::Resized) return event_window_resized(event);
			if(!ImGui::GetIO().WantCaptureKeyboard) {
				if(event.type == sf::Event::KeyPressed) return event_button_pressed(event);
				if(event.type == sf::Event::MouseMoved) return event_mouse_move(event, window);
			}
			if(!ImGui::GetIO().WantCaptureMouse) {
				if(event.type == sf::Event::MouseButtonPressed)  return event_mouse_button_pressed(event);
				if(event.type == sf::Event::MouseButtonReleased) return event_mouse_button_released(event);
			}
		}
		return std::nullopt;
	}
}
