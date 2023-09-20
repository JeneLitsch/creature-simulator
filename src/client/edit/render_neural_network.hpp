#pragma once
#include "SFML/Graphics.hpp"
#include "sim/Ecs.hpp"

namespace client::edit {
	void render_neural_network(sim::NeuralNetwork &, sf::RenderTarget &, const sim::NeuralNetConfig & config);
}