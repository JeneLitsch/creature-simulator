#pragma once
#include <memory>
#include "Event.hpp"
#include "stdxx/math.hxx"

namespace client::core {
	class StateManager;
	class GameState {
	public:
		void link(StateManager & state_manager);

		void events(const Event & event);
		virtual void update(double dt) = 0;
		virtual void ui(stx::vector2f window_size) {};
		virtual void render(sf::RenderTarget & render_target) = 0;

		virtual ~GameState() = default;
	protected:
		virtual void init() = 0;

		void push(std::unique_ptr<GameState> state);
		void pop();
		void clear();
	private:
		virtual void on_event(const Closed &) {}
		virtual void on_event(const WindowResized &) {}
		virtual void on_event(const ButtonPressed &) {}
		StateManager * state_manager = nullptr;
	};
}
