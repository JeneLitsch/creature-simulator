#pragma once
#include <vector>
#include <iostream>
#include <numeric>
#include <numbers>
#include <cmath>

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

constexpr auto sigmoid(double x) {
	return 1 / (1 + std::exp(-x));
}

struct NeuralNetwork {
	NeuralNetwork(
		std::size_t input_size,
		std::size_t output_size) 
	: input_size{input_size}, output_size{output_size} {
		inputMatrix.resize(input_size, std::vector<double>{});
		for(int i = 0; i<input_size; i++){
			inputMatrix.at(i).resize(input_size, 0.0);
			inputMatrix.at(i).at(i) = 1.0;
		}
		outputMatrix.resize(input_size, std::vector<double>{});
		for(int i = 0; i<input_size; i++){
			outputMatrix.at(i).resize(output_size, 0.0);
		}
	}

	void addNode(){
		hidden_size ++;
		inputMatrix.resize(input_size + hidden_size, std::vector<double>{});
		for(std::vector<double>& vec: inputMatrix){
			vec.resize(input_size + hidden_size, 0.0);
		}
		outputMatrix.resize(input_size + hidden_size, std::vector<double>{});
		outputMatrix.at(input_size + hidden_size - 1).resize(output_size, 0.0);
	}

	std::vector<double> eval(const std::vector<double> & input) const {
		if (input.size() != input_size) {
			throw std::runtime_error{"Input does not match input layer"};
		}
		std::vector<double> inputWithHidden = input;
		inputWithHidden.resize(input_size + hidden_size, 0.0);
		std::vector<double> out = vectorMatrixMult(vectorMatrixMult(inputWithHidden, inputMatrix), outputMatrix);
		for(double& num : out){
			num = sigmoid(num);
		}
		return out;
	}

	std::vector<std::vector<double>> inputMatrix;
	std::vector<std::vector<double>> outputMatrix;
	std::size_t input_size;
	std::size_t hidden_size = 0;
	std::size_t output_size;
};
