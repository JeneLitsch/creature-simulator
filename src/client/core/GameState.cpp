#include "GameState.hpp"
#include "StateManager.hpp"

namespace client::core {
	void GameState::link(StateManager & state_manager) {
		this->state_manager = &state_manager;
		this->init();
	}



	void GameState::events(const Event & event) {
		std::visit([this] (const auto & e) { this->on_event(e); }, event);
	}



	void GameState::push(std::unique_ptr<GameState> state) {
		this->state_manager->push(std::move(state));
	}



	void GameState::pop() {
		this->state_manager->pop();
	}



	void GameState::clear() {
		this->state_manager->clear();
	}



	void GameState::ui(stx::vector2f window_size) {

	}
}