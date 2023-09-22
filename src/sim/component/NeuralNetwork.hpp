#pragma once
#include <vector>
#include <cstdint>

namespace sim{
	struct NeuralNetConfig {
		double mutation_rate_per_weight = 0.05;
		double chance_for_new_node = 0.01;
		double weight_min = -4.0;
		double weight_max = 4.0;
		bool limit_number_of_mutations = false;
		int mutation_rolls = 2; // = max mutations per child
		double chance_per_roll = 0.5;
		bool limit_weight_change = false;
		double max_weight_change = 0.25;
		int max_hidden_nodes = 5;
		bool use_tanh_for_hidden = true;
	};

	struct NeuralNetwork {
		NeuralNetwork(std::size_t input_size, std::size_t output_size);
		void add_node();
		std::vector<double> eval(const std::vector<double> & input, const NeuralNetConfig & config) const;
		NeuralNetwork create_child(std::uint64_t seed, const NeuralNetConfig & config, double mutation_dampener);

		std::vector<std::vector<double>> input_matrix;
		std::vector<std::vector<double>> hidden_matrix;
		std::vector<std::vector<double>> output_matrix;
		std::size_t input_size;
		std::size_t hidden_size = 0;
		std::size_t output_size;
	};

	void mutate(NeuralNetwork & net, std::uint64_t seed, const NeuralNetConfig & config, double mutation_dampener);
}
