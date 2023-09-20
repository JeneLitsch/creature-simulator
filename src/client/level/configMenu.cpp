#include "imgui.h"
#include "sim/Ecs.hpp"

namespace client::level {
    void nnConfig(sim::NeuralNetConfig & config){
        if (ImGui::CollapsingHeader("Neural_Net")){
            ImGui::Checkbox("limit number of mutations", &config.limit_number_of_mutations);
            ImGui::SameLine();ImGui::Checkbox("limit weight change", &config.limit_weight_change);

            ImGui::Spacing();
            ImGui::SliderDouble("Mutation Rate per weight", &config.mutation_rate_per_weight, 0.0, 1.0);
            ImGui::InputDouble("Input Mutation Rate", &config.mutation_rate_per_weight);
            ImGui::Spacing();

            ImGui::Spacing();
            ImGui::SliderDouble("Chance for new node", &config.chance_for_new_node, 0.0, 1.0);
            ImGui::InputDouble("Input Chance", &config.chance_for_new_node);
            ImGui::Spacing();

            ImGui::Spacing();
            ImGui::SliderDouble("Weight minimum", &config.weight_min, 0.0, 1.0);
            ImGui::InputDouble("Input weight min", &config.weight_min);
            ImGui::Spacing();

            ImGui::Spacing();
            ImGui::SliderDouble("Weight maximum", &config.weight_max, 0.0, 1.0);
            ImGui::InputDouble("Input weight max", &config.weight_max);
            ImGui::Spacing();

            ImGui::Spacing();
            ImGui::SliderInt("Mutation Rolls", &config.mutation_rolls, 0, 10);
            ImGui::InputInt("Input Mutation rolls", &config.mutation_rolls);
            ImGui::Spacing();

            ImGui::Spacing();
            ImGui::SliderDouble("Chance per Roll", &config.chance_per_roll, 0.0f, 1.0f);
            ImGui::InputDouble("Input Chance per Roll", &config.chance_per_roll);
            ImGui::Spacing();

            ImGui::Spacing();
            ImGui::SliderDouble("Max weight change", &config.max_weight_change, 0.0f, 1.0f);
            ImGui::InputDouble("Input Max weight change", &config.max_weight_change);
            ImGui::Spacing();

            ImGui::Spacing();
            ImGui::SliderInt("Maximum of hidden nodes", &config.max_hidden_nodes, 1, 100);
            ImGui::InputInt("Input Max hidden nodes", &config.max_hidden_nodes);
            ImGui::Spacing();
        }
    }


    void reproductionConfig(sim::ReproductionConfig & config){
        if (ImGui::CollapsingHeader("Reproduction_Config")){

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

    void metabolismConfig(sim::MetabolismConfig & config) {
        if (ImGui::CollapsingHeader("Metabolism_Config")){
            ImGui::Spacing();
            ImGui::SliderDouble("Natural food decay per tick", &config.naturalfoodDecayPerTick, 0.0f, 1.0f);
            ImGui::InputDouble("Input Natural food decay per tick", &config.naturalfoodDecayPerTick);
            ImGui::Spacing();

            ImGui::Spacing();
            ImGui::SliderDouble("starving health decay", &config.starvingHealthDecayPerTick, 0.0f, 1.0f);
            ImGui::InputDouble("Input starving health decay", &config.starvingHealthDecayPerTick);
            ImGui::Spacing();

            ImGui::Spacing();
            ImGui::SliderDouble("Health Regen per Tick", &config.healthRegenPerTick, 0.0f, 1.0f);
            ImGui::InputDouble("Input Health Regen per Tick", &config.healthRegenPerTick);
            ImGui::Spacing();

            ImGui::Spacing();
            ImGui::SliderDouble("Food used to heal", &config.foodPerHealthRegenerated, 0.0f, 100.0f, "%.3f", ImGuiSliderFlags_Logarithmic);
            ImGui::InputDouble("Input Food used to heal", &config.healthRegenPerTick);
            ImGui::Spacing();
        };
    }

    void Menu(uint16_t& tick_speed, sim::Config& config) {
        ImGui::Begin("config");
        ImGui::SliderUInt16("tick_speed", &tick_speed, 1, 1000, "%d");
        ImGui::SliderUInt16("Age", &config.maxAge, 100, 10000, "%d", ImGuiSliderFlags_Logarithmic);
        ImGui::SliderDouble("sensors", &config.sensors.sensibility, 0.0f, 200.0f);
        ImGui::Checkbox("enable long oscilator", &config.enable_long_oscilator);
        ImGui::SameLine();ImGui::Checkbox("enable short ocsilator", &config.enable_short_oscilator);
        nnConfig(config.neural_net);
        reproductionConfig(config.reproduction);
        metabolismConfig(config.metabolism);
        ImGui::End();
    }
}
