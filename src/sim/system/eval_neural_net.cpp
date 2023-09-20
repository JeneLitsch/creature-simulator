#include "eval_neural_net.hpp"

namespace sim {
	constexpr auto sigmoid(double x) {
		return 1 / (1 + std::exp(-x));
	}

	void eval_neural(Ecs::Entity & entity, const Config& config, double oscilatorShort, double oscilatorLong){
		Age* age = entity.get_if<Age>();
		Stomach* stomach = entity.get_if<Stomach>();
		Health* health = entity.get_if<Health>();
		StomachSensorFB* sensor1 = entity.get_if<StomachSensorFB>();
		StomachSensorLR* sensor2 = entity.get_if<StomachSensorLR>();
		EdibleSensorFB* sensor3 = entity.get_if<EdibleSensorFB>();
		EdibleSensorLR* sensor4 = entity.get_if<EdibleSensorLR>();
		BarrierSensorFB* sensor5 = entity.get_if<BarrierSensorFB>();
		BarrierSensorLR* sensor6 = entity.get_if<BarrierSensorLR>();
		Movement* movement = entity.get_if<Movement>();

		if(!age || !stomach|| !health|| !sensor1|| !sensor2|| !sensor3|| !sensor4 || !movement)
			return;

        std::vector<double> input;
		input.push_back(oscilatorShort);
		input.push_back(oscilatorLong);
		input.push_back(static_cast<double>(age->age) / config.maxAge);
		input.push_back(stomach->food / config.metabolism.maxStomach);
		input.push_back(health->currentHealth);
		if(config.sensors.enable_stomach_sensor){
			input.push_back(sensor1->value);
			input.push_back(sensor2->value);
		}
		else{
			input.push_back(0.0);
			input.push_back(0.0);
		}
		if(config.sensors.enable_food_sensor){
			input.push_back(sensor3->value);
			input.push_back(sensor4->value);
		}
		else{
			input.push_back(0.0);
			input.push_back(0.0);
		}
		if(config.sensors.enable_barrier_sensor){
			input.push_back(sensor5->value);
			input.push_back(sensor6->value);
		}
		else{
			input.push_back(0.0);
			input.push_back(0.0);
		}
		input.push_back(movement->direction.x);
		input.push_back(movement->direction.y);
		input.push_back(sigmoid(movement->same_move));

        NeuralNetwork* neuralNetwork = entity.get_if<NeuralNetwork>();

		if(!neuralNetwork)
			return;

		std::vector<double> output = neuralNetwork->eval(input, config.neural_net);

		Reproduction* reproduction = entity.get_if<Reproduction>();
		if(reproduction)
			reproduction->wants_to_reproduce = output[0] >= -0.5;
        Transform* transform = entity.get_if<Transform>();
		double alpha = std::atan2(transform->rotation.y, transform->rotation.x);
		stx::vector2d direction;
		direction.x = std::cos(alpha) * output[1]  - std::sin(alpha) * output[2];
		direction.y = std::sin(alpha) * output[1]  + std::cos(alpha) * output[2];

		if(stx::hypot(direction) > 0.1){
			direction = stx::normalized(direction);
			double max = 0;
			for(int i = -1; i<=1; i++){
				for(int j = -1; j<=1; j++){
					stx::vector2d temp = stx::normalized(stx::vector2d{static_cast<double>(i), static_cast<double>(j)});
					if(stx::dot(temp, direction) > max){
						max = stx::dot(temp, direction);
						stx::vector2i new_direction = {i, j};
						if(new_direction != movement->direction){
							movement->same_move = 0;
						}
						movement->direction = new_direction;
					}
				}
			}
		}
		else{
			if(movement->direction != stx::vector2i{0, 0}){
				movement->same_move = 0;
			}
			movement->direction = 0;
		}
		movement->same_move++;

		stomach->shareFood = output[3] >= 0.0;
    }
}
