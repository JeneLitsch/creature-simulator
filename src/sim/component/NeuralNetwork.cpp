#include "NeuralNetwork.hpp"
#include "xoshiro256.h"
#include <iostream>
#include <numeric>
#include <numbers>
#include <cmath>
#include <random>
#include <algorithm>
#include "stdxx/array.hxx"

namespace sim{
	std::vector<double> vectorMatrixMult(const std::vector<double>& vec, const std::vector<std::vector<double>>& mat){
		if (vec.size() != mat.size()) {
			throw std::runtime_error{"Vector and Matrix sizes do not match"};
		}
		std::vector<double> out;
		out.resize(mat.at(0).size(), 0.0);
		for(int i = 0; i<mat.at(0).size(); i++){
			for(int j = 0; j<mat.size(); j++){
				out.at(i) += mat.at(j).at(i) * vec.at(j);
			}
		}
		return out;
	}

	NeuralNetwork::NeuralNetwork(
		std::size_t input_size,
		std::size_t output_size) 
	: input_size{input_size}, output_size{output_size} {
		inputMatrix.resize(input_size, std::vector<double>{});
		hiddenMatrix.resize(input_size, std::vector<double>{});
		for(int i = 0; i<input_size; i++){
			hiddenMatrix.at(i).resize(input_size, 0.0);
			hiddenMatrix.at(i).at(i) = 1.0;
		}
		outputMatrix.resize(input_size, std::vector<double>{});
		for(int i = 0; i<input_size; i++){
			outputMatrix.at(i).resize(output_size, 0.0);
		}
		lastOutput.resize(output_size, 0);
	}

	void NeuralNetwork::addNode(){
		hidden_size ++;
		hiddenMatrix.resize(input_size + hidden_size, std::vector<double>{});
		for(std::vector<double>& vec: inputMatrix){
			vec.resize(hidden_size, 0.0);
		}
		for(std::vector<double>& vec: hiddenMatrix){
			vec.resize(input_size + hidden_size, 0.0);
		}
		outputMatrix.resize(input_size + hidden_size, std::vector<double>{});
		outputMatrix.at(input_size + hidden_size - 1).resize(output_size, 0.0);
	}

	std::vector<double> NeuralNetwork::eval(const std::vector<double> & input, const NeuralNetConfig & config) const {
		if (input.size() != input_size) {
			throw std::runtime_error{"Input does not match input layer"};
		}
		std::vector<double> hidden = vectorMatrixMult(input, inputMatrix);
		std::vector<double> inputWithHidden = input + hidden;
		std::vector<double> out;
		if(config.use_tanh_for_hidden){
			for(int i = input_size; i<inputWithHidden.size(); i++){
				inputWithHidden.at(i) = std::tanh(inputWithHidden.at(i));
			}
			inputWithHidden = vectorMatrixMult(inputWithHidden, hiddenMatrix);
			for(int i = input_size; i<inputWithHidden.size(); i++){
				inputWithHidden.at(i) = std::tanh(inputWithHidden.at(i));
			}
			out = vectorMatrixMult(inputWithHidden, outputMatrix);
		}
		else{
			out = vectorMatrixMult(vectorMatrixMult(inputWithHidden, hiddenMatrix), outputMatrix);
		}

		for(double& num : out){
			num = std::tanh(num);
		}
		
		return out;
	}

	NeuralNetwork NeuralNetwork::createChild(std::uint64_t seed, const NeuralNetConfig & config, double mutationDampener){
		NeuralNetwork child = *this;
		mutate(child, seed, config, mutationDampener);
		return child;
	}

	bool to_be_mutated(double p, Xoshiro::Xoshiro256PP& rng) {
		std::uniform_real_distribution interval { 0.0, 1.0 };
		return interval(rng) < p;
	}

	double change_weight(double weight_value, Xoshiro::Xoshiro256PP& rng, const NeuralNetConfig & config, std::uniform_real_distribution<double>& weight_interval){
		if(config.limit_weight_change){
			double value = std::clamp(weight_interval(rng), weight_value - config.max_weight_change, weight_value + config.max_weight_change);
			return std::clamp(value, config.weight_min, config.weight_max);
		}
		return weight_interval(rng);

	}

	void mutate(NeuralNetwork & net, std::uint64_t seed, const NeuralNetConfig & config, double mutationDampener) {
		Xoshiro::Xoshiro256PP rng;
		rng.seed(seed);
		if(to_be_mutated(config.chance_for_new_node - mutationDampener * config.chance_for_new_node, rng) && net.hidden_size < config.max_hidden_nodes){
			net.addNode();
		}
		std::uniform_real_distribution weight_interval {config.weight_min, config.weight_max};
		if(config.limit_number_of_mutations){
			for(int i = 0; i < config.mutation_rolls; i++){
				if(!to_be_mutated(config.chance_per_roll - mutationDampener * config.chance_per_roll, rng)){
					continue;
				}
				int matrix_index = rng() % 3;
				if(matrix_index == 0 && net.hidden_size > 0){
					int i = rng() % net.input_size;
					int j = rng() % net.hidden_size;
					net.inputMatrix.at(i).at(j) = change_weight(net.inputMatrix.at(i).at(j), rng, config, weight_interval);
					
				}
				if(matrix_index == 1 && net.hidden_size > 0){
					int i = rng() % (net.input_size + net.hidden_size);
					int j = rng() % net.hidden_size;
					j += net.input_size;
					net.hiddenMatrix.at(i).at(j) = change_weight(net.hiddenMatrix.at(i).at(j), rng, config, weight_interval);
					
				}
				if(matrix_index == 2){
					int i = rng() % (net.input_size + net.hidden_size);
					int j = rng() % net.output_size;
					net.outputMatrix.at(i).at(j) = change_weight(net.outputMatrix.at(i).at(j), rng, config, weight_interval);
					
				}
			}
		}
		else{
			for(int i = 0; i<net.input_size; i++){
				for(int j = net.input_size; j<net.hidden_size; j++){
					if(to_be_mutated(config.mutation_rate_per_weight, rng)){
						net.inputMatrix.at(i).at(j) = change_weight(net.inputMatrix.at(i).at(j), rng, config, weight_interval);
					}
				}
			}
			for(int i = 0; i<net.input_size + net.hidden_size; i++){
				for(int j = net.input_size; j<net.input_size + net.hidden_size; j++){
					if(to_be_mutated(config.mutation_rate_per_weight, rng)){
						net.hiddenMatrix.at(i).at(j) = change_weight(net.hiddenMatrix.at(i).at(j), rng, config, weight_interval);
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
}
