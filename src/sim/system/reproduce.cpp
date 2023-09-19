#include "reproduce.hpp"
#include "sim/create.hpp"

namespace sim{
	namespace {
		std::optional<stx::vector2i> find_empty_neighbor(
			stx::grid2<std::uint64_t> & grid,
			const stx::vector2i parent_position) {

			const stx::vector2i from = stx::vector2i{0,0};
			const stx::vector2i to = stx::vector2i{
				static_cast<int>(grid.size().x - 1),
				static_cast<int>(grid.size().y - 1)
			};
			
			for(int i = -1; i <= 1; ++i) {
			    for(int j = -1; j <= 1; ++j) {
					const stx::vector2i offset = stx::vector2i{ i , j };
					const stx::vector2i child_position = stx::clamp(parent_position + offset, from, to);
			        const std::uint64_t other_id = grid[child_position];
			        if(other_id == 0){
						return child_position;
                    }
                }
            }
			return std::nullopt;
		}



		double consume_food(Stomach & stomach, const ReproductionConfig & config) {
			stomach.food -= config.food_cost;
			return stomach.food /= 2;
		}



		void spawn_child(
			Ecs & ecs,
			stx::vector2i position,
			stx::grid2<std::uint64_t> & grid,
			const Config & config,
			Reproduction & reproduction,
            NeuralNetwork& neuralNet,
            Age & age,
			Sprite & sprite,
			double initial_food_value,
            Xoshiro::Xoshiro256PP & rng) {
			
			Ecs::Entity & child = create_creature(ecs, position, grid, config, initial_food_value);
            child.add(neuralNet.createChild(rng(), config.neural_net, age.age / config.maxAge));
			child.add(sprite.createChild(rng(), config.reproduction, age.age / config.maxAge));
		}
	}



    void reproduce(Ecs::Entity& entity, stx::grid2<std::uint64_t>* grid, Ecs* ecs, PheromoneField* pheromone_field, const Config& config, Xoshiro::Xoshiro256PP & rng){
        auto * reproduction = entity.get_if<Reproduction>();
		auto * stomach = entity.get_if<Stomach>();
		auto * transform = entity.get_if<Transform>();
        auto * neuralNet = entity.get_if<NeuralNetwork>();
        auto * age = entity.get_if<Age>();
		auto * sprite = entity.get_if<Sprite>();

		if(!reproduction) return; 
		if(!stomach) return;
		if(!transform) return;
        if(!neuralNet) return;
        if(!age) return;
		if(!stomach) return;
		if(!sprite) return;

        reproduction->incrementCooldown();

        if(reproduction->current_cooldown >= reproduction->max_cooldown && reproduction->wants_to_reproduce && stomach->food >= config.reproduction.food_cost){
            const auto child_position = find_empty_neighbor(*grid, transform->location);
			if(child_position) {
				double food = consume_food(*stomach, config.reproduction);
				spawn_child(*ecs, *child_position, *grid, config, *reproduction, *neuralNet, *age, *sprite, food, rng);
			}
            else {
				return;
			}
        }
    }
}
