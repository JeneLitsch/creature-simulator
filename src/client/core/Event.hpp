#pragma once
#include <variant>
#include <optional>
#include <SFML/Graphics.hpp>

namespace client::core {
	struct Closed {};
	struct WindowResized {};

	using Event = std::variant<
		Closed,
		WindowResized
	>;

	std::optional<Event> fetch_event(sf::Window & window);
}