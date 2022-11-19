#include "Level.hpp"

namespace client::level {
	void init_entities(Ecs & ecs) {
		for(std::size_t i = 0; i < 100; ++i) {
			auto & entity = ecs.new_entity();
			entity.add<Sprite>({});
			entity.add<Position>({});
		}
	}



	Level::Level() {
		init_entities(this->ecs);
	}



	void Level::update(double dt) {

	}
	
	
	
	void Level::render(sf::RenderTarget & render_target) {

	}
	
	
	
	void Level::init() {

	}
}
