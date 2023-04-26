#pragma once
#include <vector>
#include <iostream>
#include <numeric>
#include <numbers>
#include <cmath>


constexpr auto sigmoid(auto x) {
	const auto e = std::numbers::e_v<decltype(x)>;
	return 1 / (1 + std::pow(e, -x)); 
}



struct Layer {
	Layer(std::size_t count) {
		biases.resize(count, 0.0);
	}
	std::vector<double> biases;

	std::vector<double> eval(const std::vector<double> & input) const {
		if (biases.size() != input.size()) {
			throw std::runtime_error{"Input does not match layer size"};
		}
		
		std::vector<double> output;
		for(std::size_t i = 0; i < input.size(); ++i) {
			output.push_back(sigmoid(input[i] + biases[i]));
		}
		return output;
	}
};



struct Transition {
	Transition(std::size_t count) {
		weights.resize(count, 1.0);
	}
	std::vector<double> weights;

	std::vector<double> eval(const std::vector<double> & input) const {
		std::vector<double> output;
		const auto i_max = input.size();
		const auto k_max = weights.size() / i_max;
		for(std::size_t k = 0; k < k_max; ++k) {
			double result = 0.0;
			for(std::size_t i = 0; i < i_max; ++i) {
				const auto w = weights[i * k_max + k];
				result += w * input[i];
			}
			output.push_back(result);
		}
		return output;
	}
};



struct NeuralNetwork {
	NeuralNetwork(
		std::size_t input_size,
		const std::vector<std::size_t> & layer_sizes) 
	: input_size{input_size} {
		std::size_t last_size = input_size;
		for (const auto size : layer_sizes) {
			this->layers.push_back(Layer{size});
			this->transitions.push_back(Transition{last_size * size});
			last_size = size;
		}
	}


	std::vector<double> eval(const std::vector<double> & input) const {
		if (input.size() != input_size) {
			throw std::runtime_error{"Input does not match input layer"};
		}

		std::vector<double> last = input;
		for(std::size_t i = 0; i < transitions.size(); ++i) {
			const auto layer_input = transitions[i].eval(last);
			// std::cout << "Transition " << i << ": " << layer_input.size() << "\n"; 
			const auto layer_ouput = layers[i].eval(layer_input);
			last = layer_ouput;
		}
		return last;
	}

	std::vector<Layer> layers;
	std::vector<Transition> transitions;
	std::size_t input_size;
};
