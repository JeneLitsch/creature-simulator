#pragma once
#include <variant>
#include <optional>
#include <SFML/Graphics.hpp>

namespace client::core {
	struct Closed {};
	struct WindowResized {};
	struct ButtonPressed {
        sf::Keyboard::Key code;    ///< Code of the key that has been pressed
        bool          alt;     ///< Is the Alt key pressed?
        bool          control; ///< Is the Control key pressed?
        bool          shift;   ///< Is the Shift key pressed?
        bool          system;  ///< Is the System key pressed?

    };

	using Event = std::variant<
		Closed,
		WindowResized,
        ButtonPressed
	>;

	std::optional<Event> fetch_event(sf::Window & window);
}
