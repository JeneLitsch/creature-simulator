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



		void consume_food(Stomach & stomach, const ReproductionConfig & config) {
			stomach.food -= config.food_cost;
		}



		void spawn_child(
			Ecs & ecs,
			stx::vector2i position,
			stx::grid2<std::uint64_t> & grid,
			const Config & config,
			Reproduction & reproduction,
            NeuralNetwork& neuralNet,
			std::mt19937_64 & rng) {
			
			Ecs::Entity & child = create_creature(ecs, position, grid, config);
			child.add(reproduction.createChild(rng(), config.reproduction));
            child.add(neuralNet.createChild(rng(), config.neural_net));
		}
	}



    void reproduce(Ecs::Entity& entity, stx::grid2<std::uint64_t>* grid, Ecs* ecs, PheromoneField* pheromone_field, const Config& config, std::mt19937_64 & rng){
        auto * reproduction = entity.get_if<Reproduction>();
		auto * stomach = entity.get_if<Stomach>();
		auto * transform = entity.get_if<Transform>();
        auto * neuralNet = entity.get_if<NeuralNetwork>();

		if(!reproduction) return; 
		if(!stomach) return;
		if(!transform) return;
        if(!neuralNet) return;

        reproduction->incrementCooldown();

        if(reproduction->current_cooldown >= reproduction->max_cooldown && reproduction->wants_to_reproduce){
            const auto child_position = find_empty_neighbor(*grid, transform->location);
			if(child_position) {
				consume_food(*stomach, config.reproduction);
				spawn_child(*ecs, *child_position, *grid, config, *reproduction, *neuralNet, rng);
			}
            else {
				return;
			}
        }
    }
}