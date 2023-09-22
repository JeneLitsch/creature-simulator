#include "imgui.h"
#include "sim/Ecs.hpp"

namespace client::level {
    void nn_config(sim::NeuralNetConfig & config){
        if (ImGui::CollapsingHeader("Neural Networks")){
            ImGui::Checkbox("Limit number of mutations", &config.limit_number_of_mutations);
            ImGui::Spacing();

            if(config.limit_number_of_mutations){
                ImGui::Spacing();
                ImGui::SliderInt("Mutation Rolls", &config.mutation_rolls, 0, 10);
                ImGui::InputInt("Input Mutation rolls", &config.mutation_rolls);
                ImGui::Spacing();

                ImGui::Spacing();
                ImGui::SliderDouble("Chance per Roll", &config.chance_per_roll, 0.0f, 1.0f);
                ImGui::InputDouble("Input Chance per Roll", &config.chance_per_roll);
                ImGui::Spacing();
            }
            else{
                ImGui::Spacing();
                ImGui::SliderDouble("Mutation Rate per weight", &config.mutation_rate_per_weight, 0.0, 1.0);
                ImGui::InputDouble("Input Mutation Rate", &config.mutation_rate_per_weight);
                ImGui::Spacing();
            }
            
            ImGui::Checkbox("Limit weight change", &config.limit_weight_change);
            ImGui::Spacing();

            if(config.limit_weight_change){
                ImGui::Spacing();
                ImGui::SliderDouble("Max weight change", &config.max_weight_change, 0.0f, 1.0f);
                ImGui::InputDouble("Input Max weight change", &config.max_weight_change);
                ImGui::Spacing();
            }

            ImGui::Checkbox("Use tanh for hidden layer", &config.use_tanh_for_hidden);
            ImGui::Spacing();

            ImGui::Spacing();
            ImGui::SliderDouble("Chance for new hidden node", &config.chance_for_new_node, 0.0, 1.0);
            ImGui::InputDouble("Input Chance for new hidden node", &config.chance_for_new_node);
            ImGui::Spacing();

            ImGui::Spacing();
            ImGui::SliderInt("Maximum of hidden nodes", &config.max_hidden_nodes, 1, 100);
            ImGui::InputInt("Input Max hidden nodes", &config.max_hidden_nodes);
            ImGui::Spacing();

            ImGui::Spacing();
            ImGui::SliderDouble("Weight minimum", &config.weight_min, -10.0, 0.0);
            if(ImGui::InputDouble("Input weight min", &config.weight_min)){
                if(config.weight_min > 0) config.weight_min = 0;
            }
            ImGui::Spacing();

            ImGui::Spacing();
            ImGui::SliderDouble("Weight maximum", &config.weight_max, 0.0, 10.0);
            if(ImGui::InputDouble("Input weight max", &config.weight_max)){
                if(config.weight_max < 0) config.weight_max = 0;
            }
            ImGui::Spacing();
        }
    }


    void reproduction_config(sim::ReproductionConfig & config){
        if (ImGui::CollapsingHeader("Reproduction")){

            ImGui::Spacing();
            ImGui::SliderUInt64("Reproduction cooldown", &config.cooldown, 1, 10000, "%d", ImGuiSliderFlags_Logarithmic);
            ImGui::InputUInt64("Input Reproduction cooldown", &config.cooldown);
            ImGui::Spacing();

            ImGui::Spacing();
            ImGui::SliderDouble("Reproduction food cost", &config.food_cost, 0.0, 10.0);
            ImGui::InputDouble("Input Reproduction food cost", &config.food_cost);
            ImGui::Spacing();
        }
    }

    void entity_sensor_config(sim::EntitySensorConfig & config){
        if (ImGui::CollapsingHeader("Entity Sensor")){
            ImGui::Checkbox("Enable food Sensor", &config.enable_food_sensor);
            ImGui::Spacing();
            ImGui::Checkbox("Enable creature Sensor", &config.enable_stomach_sensor);
            ImGui::Spacing();
            ImGui::Checkbox("Enable barrier Sensor", &config.enable_barrier_sensor);
            ImGui::Spacing();

            ImGui::Spacing();
            ImGui::SliderDouble("Sensor sensibility", &config.sensibility, 0.0f, 200.0f);
            ImGui::InputDouble("Input sensor sensibility", &config.sensibility);            
            ImGui::Spacing();

            ImGui::Spacing();
            ImGui::SliderInt("Sensor radius", &config.radius, 0, 1024);
            if(ImGui::InputInt("Input sensor radius", &config.radius)){
                std::clamp(config.radius, 0, 1024);
            }       
            ImGui::Spacing();

        }
    }

    void metabolism_config(sim::MetabolismConfig & config) {
        if (ImGui::CollapsingHeader("Metabolism")){
            ImGui::Spacing();
            ImGui::SliderDouble("Maximum Stomach capacity", &config.max_stomach, 0.1f, 100.0f, "%.3f", ImGuiSliderFlags_Logarithmic);
            ImGui::InputDouble("Input Maximum Stomach capacity", &config.max_stomach);
            ImGui::Spacing();

            ImGui::Spacing();
            ImGui::SliderDouble("Natural food decay per tick", &config.natural_food_decay_per_tick, 0.0f, 1.0f);
            ImGui::InputDouble("Input Natural food decay per tick", &config.natural_food_decay_per_tick);
            ImGui::Spacing();

            ImGui::Spacing();
            ImGui::SliderDouble("Food decay per move", &config.food_decay_per_move, 0.0f, 1.0f);
            ImGui::InputDouble("Input food decay per move", &config.food_decay_per_move);
            ImGui::Spacing();

            ImGui::Spacing();
            ImGui::SliderDouble("Starving health decay", &config.starving_health_decay_per_tick, 0.0f, 1.0f);
            ImGui::InputDouble("Input starving health decay", &config.starving_health_decay_per_tick);
            ImGui::Spacing();

            ImGui::Spacing();
            ImGui::SliderDouble("Health Regen per Tick", &config.health_regen_per_tick, 0.0f, 1.0f);
            ImGui::InputDouble("Input Health Regen per Tick", &config.health_regen_per_tick);
            ImGui::Spacing();

            ImGui::Spacing();
            ImGui::SliderDouble("Food used to heal", &config.food_per_health_regenerated, 0.0f, 100.0f, "%.3f", ImGuiSliderFlags_Logarithmic);
            ImGui::InputDouble("Input Food used to heal", &config.health_regen_per_tick);
            ImGui::Spacing();

            ImGui::Spacing();
            ImGui::Checkbox("Enable food sharing", &config.enable_food_sharing);
            ImGui::SliderDouble("Food shared per tick", &config.food_shared, 0.0f, 100.0f, "%.3f", ImGuiSliderFlags_Logarithmic);
            ImGui::InputDouble("Input food shared per tick", &config.food_shared);
            ImGui::Spacing();
        };
    }

    void Menu(uint16_t& tick_speed, sim::Config& config) {
        ImGui::Begin("config");
        ImGui::SliderUInt16("Tick speed", &tick_speed, 1, 60, "%d");
        ImGui::SliderUInt16("Maximum Age", &config.max_age, 100, 10000, "%d", ImGuiSliderFlags_Logarithmic);
        ImGui::Checkbox("Enable long oscilator", &config.enable_long_oscilator);
        ImGui::SameLine();ImGui::Checkbox("Enable short ocsilator", &config.enable_short_oscilator);
        nn_config(config.neural_net);
        reproduction_config(config.reproduction);
        metabolism_config(config.metabolism);
        entity_sensor_config(config.sensors);
        ImGui::End();
    }
}
