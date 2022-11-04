#pragma once
#include <queue>
#include "GameState.hpp"

namespace core {

	class StateManager {
	public:
		struct Push {
			std::unique_ptr<GameState> state;
		};

		struct Pop {};

		void push(std::unique_ptr<GameState> state);
		void pop();

		void handle_queue();
		void events(const Event & event);
		void update(double dt);
		void render(sf::RenderTarget & render_target);
	private:
		void execute(Push push);
		void execute(Pop pop);

		std::vector<std::unique_ptr<GameState>> states;
		std::queue<std::variant<Push, Pop>> queue;
	};
}