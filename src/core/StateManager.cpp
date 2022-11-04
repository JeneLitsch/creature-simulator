#include "StateManager.hpp"

namespace core {
	void StateManager::push(std::unique_ptr<GameState> state) {
		this->queue.push(Push{
			.state = std::move(state)
		});
	}



	void StateManager::pop() {
		this->queue.push(Pop{});
	}



	void StateManager::handle_queue() {
		while(!this->queue.empty()) {
			auto & command = this->queue.front();
			std::visit([this] (auto & c) { this->execute(std::move(c)); }, command);
			queue.pop();
		}
	}



	void StateManager::events(const Event & event) {
		if(!this->states.empty()) this->states.back()->events(event);

	}


	
	void StateManager::update(double dt) {
		if(!this->states.empty()) this->states.back()->update(dt);
	}
	
	
	
	void StateManager::render(sf::RenderTarget & render_target) {
		if(!this->states.empty()) this->states.back()->render(render_target);
	}



	void StateManager::execute(Push push) {
		this->states.push_back(std::move(push.state));
		this->states.back()->link(*this);
	}



	void StateManager::execute(Pop pop) {
		this->states.pop_back();
	}
}