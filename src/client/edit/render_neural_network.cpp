#include "render_neural_network.hpp"
#include <optional>

namespace client::edit {
	void render_neural_network(
		sim::NeuralNetwork & neural_network,
		sf::RenderTarget & target) {
			
		sf::VertexArray nodes;
		nodes.setPrimitiveType(sf::Quads);

		sf::VertexArray lines;
		lines.setPrimitiveType(sf::Quads);

		std::array<std::uint64_t, 4> layer_sizes {
			neural_network.input_size,
			neural_network.input_size + neural_network.hidden_size,
			neural_network.input_size + neural_network.hidden_size,
			neural_network.output_size
		};

		const float dist_x = target.getSize().x / 5.f;
		const float dist_y = target.getSize().y / (1.f + static_cast<float>(*std::max_element(std::begin(layer_sizes), std::end(layer_sizes))));
		const float node_size =  0.125f * std::min(dist_x, dist_y);

		const auto calc_pos = [&] (std::uint64_t x, std::uint64_t y) {
			return stx::vector2f{
				dist_x + x * dist_x,
				dist_y + y * dist_y,
			};
		};


		for(std::uint64_t i_x = 0; i_x < layer_sizes.size(); ++i_x) {
			for(std::uint64_t i_y = 0; i_y < layer_sizes[i_x]; ++i_y) {
				const auto [x,y] = calc_pos(i_x, i_y);
				nodes.append(sf::Vertex{{x-node_size, y-node_size}});
				nodes.append(sf::Vertex{{x+node_size, y-node_size}});
				nodes.append(sf::Vertex{{x+node_size, y+node_size}});
				nodes.append(sf::Vertex{{x-node_size, y+node_size}});
			}
		}

		for(std::uint64_t i = 0; i + 1 < layer_sizes.size(); ++i) {
			for(std::uint64_t a = 0; a < layer_sizes[i+0]; ++a) {
				for(std::uint64_t b = 0; b < layer_sizes[i+1]; ++b) {
					const auto pos_a = calc_pos(i + 0, a);
					const auto pos_b = calc_pos(i + 1, b);

					const auto dir = stx::normalized(pos_b - pos_a);
					const auto normal = stx::rotate_90_cw(dir);

					std::optional<float> weight;

					sf::Color color = sf::Color::White;

					if(i == 0) {
						if(b >= neural_network.input_size) {
							weight = neural_network.inputMatrix[a][b];
						}
					}
					else if((i + 2) == layer_sizes.size()) {
						weight = neural_network.outputMatrix[a][b];
					}
					else {
						if((a == b) && (a < neural_network.input_size)) {
						}
						else {
							weight = neural_network.hiddenMatrix[a][b];
						}
					}

					if(weight) {
						if(weight > 0) {
							color = stx::lerp(sf::Color{255,255,255}, sf::Color{0,255,0}, std::abs(*weight));
						}
						else {
							color = stx::lerp(sf::Color{255,255,255}, sf::Color{255,0,0}, std::abs(*weight));
						}
					}
					else {
						color = sf::Color{128,128,128};
					}

					const float width = weight.value_or(a == b ? 1.f : 0.f) *  node_size * 0.25f;

					const auto offset = normal * width;
					
					lines.append(sf::Vertex{(pos_a - offset).to<sf::Vector2f>(), color});
					lines.append(sf::Vertex{(pos_a + offset).to<sf::Vector2f>(), color});
					lines.append(sf::Vertex{(pos_b + offset).to<sf::Vector2f>(), color});
					lines.append(sf::Vertex{(pos_b - offset).to<sf::Vector2f>(), color});
				}
			}
		}

		target.draw(lines);
		target.draw(nodes);
	}
}