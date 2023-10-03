#include "eval_neural_net.hpp"

namespace sim {
	constexpr auto sigmoid(double x) {
		return 1 / (1 + std::exp(-x));
	}

	void eval_neural(Ecs::Entity & entity, const Config& config, double oscilator_short, double oscilator_long){
		Age* age = entity.get_if<Age>();
		Stomach* stomach = entity.get_if<Stomach>();
		Health* health = entity.get_if<Health>();
		StomachSensorFB* sensor_1 = entity.get_if<StomachSensorFB>();
		StomachSensorLR* sensor_2 = entity.get_if<StomachSensorLR>();
		EdibleSensorFB* sensor_3 = entity.get_if<EdibleSensorFB>();
		EdibleSensorLR* sensor_4 = entity.get_if<EdibleSensorLR>();
		BarrierSensorFB* sensor_5 = entity.get_if<BarrierSensorFB>();
		BarrierSensorLR* sensor_6 = entity.get_if<BarrierSensorLR>();
		Movement* movement = entity.get_if<Movement>();

		if(!age || !stomach|| !health|| !sensor_1|| !sensor_2|| !sensor_3|| !sensor_4 || !movement)
			return;

        std::vector<double> input;
		input.push_back(oscilator_short);
		input.push_back(oscilator_long);
		input.push_back(static_cast<double>(age->age) / config.max_age);
		input.push_back(stomach->food / config.metabolism.max_stomach);
		input.push_back(health->current_health);
		if(config.sensors.enable_stomach_sensor){
			input.push_back(sensor_1->value);
			input.push_back(sensor_2->value);
		}
		else{
			input.push_back(0.0);
			input.push_back(0.0);
		}
		if(config.sensors.enable_food_sensor){
			input.push_back(sensor_3->value);
			input.push_back(sensor_4->value);
		}
		else{
			input.push_back(0.0);
			input.push_back(0.0);
		}
		if(config.sensors.enable_barrier_sensor){
			input.push_back(sensor_5->value);
			input.push_back(sensor_6->value);
		}
		else{
			input.push_back(0.0);
			input.push_back(0.0);
		}
		input.push_back(movement->direction.x);
		input.push_back(movement->direction.y);
		input.push_back(sigmoid(static_cast<double>(movement->same_move)));

        NeuralNetwork* neural_network = entity.get_if<NeuralNetwork>();

		if(!neural_network)
			return;

		std::vector<double> output = neural_network->eval(input, config.neural_net);

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

		stomach->share_food = output[3] >= 0.0;
    }
}
