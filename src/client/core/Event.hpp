#pragma once
#include <variant>
#include <optional>
#include <SFML/Graphics.hpp>

namespace client::core {
	struct Closed {};

	using Event = std::variant<
		Closed
	>;

	std::optional<Event> fetch_event(sf::Window & window);
}