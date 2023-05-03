#pragma once
#include "neural_net.hpp"
#include <random>
#include <cmath>
#include <algorithm>

struct MutConfig {
	double mutation_rate_per_weight = 0.05;
	double chance_for_new_node = 0.05;
	double weight_min = -1.0;
	double weight_max = 1.0;
};



bool to_be_mutated(double p, std::mt19937_64 rng) {
	std::uniform_real_distribution interval { 0.0, 1.0 };
	return interval(rng) < p;
}

void mutate(NeuralNetwork & net, std::uint64_t seed, const MutConfig & config) {
	std::mt19937_64 rng;
	rng.seed(seed);
	if(to_be_mutated(config.chance_for_new_node, rng)){
		net.addNode();
	}
	std::uniform_real_distribution interval {config.weight_min, config.weight_max};
	for(int i = 0; i<net.input_size + net.hidden_size; i++){
		for(int j = net.input_size; j<net.input_size + net.hidden_size; j++){
			if(to_be_mutated(config.mutation_rate_per_weight, rng)){
				net.inputMatrix.at(i).at(j) = interval(rng);
			}
		}
	}
	for(int i = 0; i<net.input_size + net.hidden_size; i++){
		for(int j = 0; j<net.output_size; j++){
			if(to_be_mutated(config.mutation_rate_per_weight, rng)){
				net.outputMatrix.at(i).at(j) = interval(rng);
			}
		}
	}
}