#pragma once
#include "neural_net.hpp"
#include <random>
#include <cmath>
#include <algorithm>

struct MutConfig {
	double mutation_rate_per_weight = 0.05;
	double chance_for_new_node = 0.01;
	double weight_min = -1.0;
	double weight_max = 1.0;
	bool limit_number_of_mutations = false;
	int mutation_rolls = 2; // = max_mutations
	double chance_per_roll = 0.5;
	bool limit_weight_change = false;
	double max_weight_change = 0.25;
};

bool to_be_mutated(double p, std::mt19937_64& rng) {
	std::uniform_real_distribution interval { 0.0, 1.0 };
	return interval(rng) < p;
}

double change_weight(double weight_value, std::mt19937_64& rng, const MutConfig & config, std::uniform_real_distribution<double>& weight_interval){
	if(config.limit_weight_change){
		double value = std::clamp(weight_interval(rng), weight_value - config.max_weight_change, weight_value + config.max_weight_change);
		return std::clamp(value, config.weight_min, config.weight_max);
	}
	return weight_interval(rng);

}

void mutate(NeuralNetwork & net, std::uint64_t seed, const MutConfig & config) {
	std::mt19937_64 rng;
	rng.seed(seed);
	if(to_be_mutated(config.chance_for_new_node, rng)){
		net.addNode();
	}
	std::uniform_real_distribution weight_interval {config.weight_min, config.weight_max};
	if(config.limit_number_of_mutations){
		for(int i = 0; i < config.mutation_rolls; i++){
			if(!to_be_mutated(config.chance_per_roll, rng)){
				continue;
			}
			int matrix_index = rng() % 2;
			if(matrix_index < 1 && net.hidden_size > 0){
				int i = rng() % (net.input_size + net.hidden_size);
				int j = rng() % net.hidden_size;
				j += net.input_size;
				net.inputMatrix.at(i).at(j) = change_weight(net.inputMatrix.at(i).at(j), rng, config, weight_interval);
				
			}
			else{
				int i = rng() % (net.input_size + net.hidden_size);
				int j = rng() % net.output_size;
				net.outputMatrix.at(i).at(j) = change_weight(net.outputMatrix.at(i).at(j), rng, config, weight_interval);
				
			}
		}
	}
	else{
		for(int i = 0; i<net.input_size + net.hidden_size; i++){
			for(int j = net.input_size; j<net.input_size + net.hidden_size; j++){
				if(to_be_mutated(config.mutation_rate_per_weight, rng)){
					net.inputMatrix.at(i).at(j) = change_weight(net.inputMatrix.at(i).at(j), rng, config, weight_interval);
				}
			}
		}
		for(int i = 0; i<net.input_size + net.hidden_size; i++){
			for(int j = 0; j<net.output_size; j++){
				if(to_be_mutated(config.mutation_rate_per_weight, rng)){
					net.outputMatrix.at(i).at(j) = change_weight(net.outputMatrix.at(i).at(j), rng, config, weight_interval);
				}
			}
		}
	}
}