#include "Level.hpp"
#include "render_entity.hpp"
#include <random>

namespace client::level {
	void init_entities(Ecs & ecs) {
		std::mt19937 rng{42};
		std::uniform_real_distribution<float> dist_x{0, 960};
		std::uniform_real_distribution<float> dist_y{0, 540};
		for(std::size_t i = 0; i < 100; ++i) {
			auto & entity = ecs.new_entity();
			entity.add(Sprite{});
			entity.add(Position{
				.position = stx::position2f{dist_x(rng), dist_y(rng)}
			});
		}
	}



	Level::Level() {
		init_entities(this->ecs);
	}



	void Level::update(double dt) {

	}
	
	
	
	void Level::render(sf::RenderTarget & render_target) {
		sf::VertexArray vertecies;
		vertecies.setPrimitiveType(sf::Quads);
		this->ecs.run_system([&] (auto & entity) {
			return render_entity(vertecies, entity);
		});
		render_target.draw(vertecies);
	}
	
	
	
	void Level::init() {

	}
}
