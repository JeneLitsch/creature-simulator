#pragma once
#include <vector>
#include <cstdint>

namespace sim{
	struct NeuralNetMutConfig {
		double mutation_rate_per_weight = 0.05;
		double chance_for_new_node = 0.01;
		double weight_min = -1.0;
		double weight_max = 1.0;
		bool limit_number_of_mutations = false;
		int mutation_rolls = 2; // = max mutations per child
		double chance_per_roll = 0.5;
		bool limit_weight_change = false;
		double max_weight_change = 0.25;
		int max_hidden_nodes = 5;
	};

	struct NeuralNetwork {
		NeuralNetwork(std::size_t input_size, std::size_t output_size);
		void addNode();
		std::vector<double> eval(const std::vector<double> & input) const;
		NeuralNetwork createChild(std::uint64_t seed, const NeuralNetMutConfig & config);

		std::vector<std::vector<double>> inputMatrix;
		std::vector<std::vector<double>> outputMatrix;
		std::size_t input_size;
		std::size_t hidden_size;
		std::size_t output_size;
	};

	void mutate(NeuralNetwork & net, std::uint64_t seed, const NeuralNetMutConfig & config);
}
