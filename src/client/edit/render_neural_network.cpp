#include "render_neural_network.hpp"
#include <optional>

namespace client::edit {
	namespace {
		sf::Color mix_color(std::optional<double> weight, const sim::NeuralNetConfig & config) {
			if(!weight)     return sf::Color{128,128,128};
			if(*weight < 0)  return stx::lerp(sf::Color::White, sf::Color::Red, std::abs(*weight / config.weight_min));
			if(*weight >= 0) return stx::lerp(sf::Color::White, sf::Color::Green, std::abs(*weight / config.weight_max));
			return sf::Color::Magenta;
		}


		std::optional<double> get_weight(sim::NeuralNetwork & neural_network, std::uint64_t i, std::uint64_t a, std::uint64_t b) {
			if(i == 0) {
				if(b >= neural_network.input_size) {
					return neural_network.input_matrix[a][b - neural_network.input_size];
				}
				else {
					return std::nullopt;
				}
			}
			else if((i + 2) == 4) {
				return neural_network.output_matrix[a][b];
			}
			else {
				if((a == b) && (a < neural_network.input_size)) {
					return std::nullopt;
				}
				else {
					return neural_network.hidden_matrix[a][b];
				}
			}
		}
	}


	void render_neural_network(
		sim::NeuralNetwork & neural_network,
		sf::RenderTarget & target,
		const sim::NeuralNetConfig & config) {
			
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

		const float dist_x = static_cast<float>(target.getSize().x) / 5.f;
		const float dist_y = static_cast<float>(target.getSize().y) / (1.f + static_cast<float>(*std::max_element(std::begin(layer_sizes), std::end(layer_sizes))));
		const float node_size =  0.125f * std::min(dist_x, dist_y);

		const auto calc_pos = [&] (std::uint64_t x, std::uint64_t y) {
			return stx::vector2f{
				dist_x + static_cast<float>(x) * dist_x,
				dist_y + static_cast<float>(y) * dist_y,
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

		for(std::uint64_t i = 0; (i + 1) < layer_sizes.size(); ++i) {
			for(std::uint64_t a = 0; a < layer_sizes[i+0]; ++a) {
				for(std::uint64_t b = 0; b < layer_sizes[i+1]; ++b) {
					const auto pos_a = calc_pos(i + 0, a);
					const auto pos_b = calc_pos(i + 1, b);

					const auto dir = stx::normalized(pos_b - pos_a);
					const auto normal = stx::rotate_90_cw(dir);

					const std::optional<double> weight = get_weight(neural_network, i, a, b);

					const sf::Color color = mix_color(weight,config);

					const float width 
						= node_size * 0.25f * (weight
						? std::abs(stx::remap(config.weight_min, config.weight_max, -1.f, 1.f, *weight))
						: a == b ? 1.f : 0.f);

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