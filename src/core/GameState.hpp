#pragma once
#include "Event.hpp"

namespace core {
	class StateManager;
	class GameState {
	public:
		void link(StateManager & state_manager);

		void events(const Event & event);
		virtual void update(double dt) = 0;
		virtual void render(sf::RenderTarget & render_target) = 0;
	protected:
		virtual void init() = 0;

		void push(std::unique_ptr<GameState> state);
		void pop();
	private:
		virtual void on_event(const Closed &) {}
		StateManager * state_manager = nullptr;
	};
}