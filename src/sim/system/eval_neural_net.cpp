#include "eval_neural_net.hpp"

namespace sim {
	void eval_neural(Ecs::Entity & entity, const Config& config){
		Age* age = entity.get_if<Age>();
		Stomach* stomach = entity.get_if<Stomach>();
		Health* health = entity.get_if<Health>();
		StomachSensorFB* sensor1 = entity.get_if<StomachSensorFB>();
		StomachSensorLR* sensor2 = entity.get_if<StomachSensorLR>();
		EdibleSensorFB* sensor3 = entity.get_if<EdibleSensorFB>();
		EdibleSensorLR* sensor4 = entity.get_if<EdibleSensorLR>();

		if(!age || !stomach|| !health|| !sensor1|| !sensor2|| !sensor3|| !sensor4)
			return;

        std::vector<double> input;
		input.push_back(static_cast<double>(age->age) / config.maxAge);
		input.push_back(stomach->food / config.metabolism.maxStomach);
		input.push_back(health->currentHealth);
		input.push_back(sensor1->value);
		input.push_back(sensor2->value);
		input.push_back(sensor3->value);
		input.push_back(sensor4->value);

        NeuralNetwork* neuralNetwork = entity.get_if<NeuralNetwork>();

		if(!neuralNetwork)
			return;

		std::vector<double> output = neuralNetwork->eval(input);

		Reproduction* reproduction = entity.get_if<Reproduction>();
		if(reproduction)
			reproduction->wants_to_reproduce = true; //output[0] >= 0.0;
        Transform* transform = entity.get_if<Transform>();
		double alpha = std::atan2(transform->rotation.y, transform->rotation.x);
		stx::vector2d direction;
		direction.x = std::cos(alpha) * output[1]  - std::sin(alpha) * output[2];
		direction.y = std::sin(alpha) * output[1]  + std::cos(alpha) * output[2];

		if(Movement* movement = entity.get_if<Movement>()){
			if(stx::hypot(direction) > 0.1){
				direction = stx::normalized(direction);
				double max = 0;
				for(int i = -1; i<=1; i++){
					for(int j = -1; j<=1; j++){
						stx::vector2d temp = stx::normalized(stx::vector2d{i, j});
						if(stx::dot(temp, direction) > max){
							max = stx::dot(temp, direction);
							movement->direction = {i, j};
						}
					}
				}
			}
			else{
				movement->direction = 0;
			}
		}
		
    }
}