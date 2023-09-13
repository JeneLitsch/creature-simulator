#pragma once
#include <queue>
#include <memory>
#include "GameState.hpp"

namespace client::core {

	class StateManager {
	public:
		struct Push {
			std::unique_ptr<GameState> state;
		};

		struct Pop {};
		
		struct Clear {};

		void push(std::unique_ptr<GameState> state);
		void pop();
		void clear();

		void handle_queue();
		void events(const Event & event);
		void update(double dt);
		void ui(stx::vector2f window_size);
		void render(sf::RenderTarget & render_target);

		bool terminated() const;
	private:
		void execute(Push push);
		void execute(Pop pop);
		void execute(Clear clear);

		std::vector<std::unique_ptr<GameState>> states;
		std::queue<std::variant<Push, Pop, Clear>> queue;
	};
}