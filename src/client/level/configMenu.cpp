#include "imgui.h"
#include "sim/Ecs.hpp"

namespace client::level {
    void nnConfig(sim::NeuralNetMutConfig & config){
        if (ImGui::CollapsingHeader("Neural_Net")){
            ImGui::Checkbox("limit number of mutations", &config.limit_number_of_mutations);
            ImGui::SameLine();ImGui::Checkbox("limit weight change", &config.limit_weight_change);
            ImGui::SliderDouble("Mutation Rate per weight", &config.mutation_rate_per_weight, 0.0f, 1.0f);
            ImGui::SliderDouble("Chance for new node", &config.chance_for_new_node, 0.0f, 1.0f);
            ImGui::SliderDouble("Weight minimum", &config.weight_min, 0.0f, 1.0f);
            ImGui::SliderDouble("Weight maximum", &config.weight_max, 0.0f, 1.0f);
            ImGui::SliderInt("Mutation Rolls", &config.mutation_rolls, 0, 10);
            ImGui::SliderDouble("Chance per Roll", &config.chance_per_roll, 0.0f, 1.0f);
            ImGui::SliderDouble("Max weight change", &config.max_weight_change, 0.0f, 1.0f);
            ImGui::SliderInt("Maximum of hidden nodes", &config.max_hidden_nodes, 1, 100);
        }
    }


    void reproductionConfig(sim::ReproductionConfig & config){
        if (ImGui::CollapsingHeader("Reproduction_Config")){
            ImGui::SliderUInt64("Max Reproduction cooldown", &config.max_reproduction_cooldown, 1, 10000, "%d", ImGuiSliderFlags_Logarithmic);
            ImGui::SliderUInt64("Min Reprocution Cooldown", &config.min_reproduction_cooldown, 1, 10000, "%d", ImGuiSliderFlags_Logarithmic);
            ImGui::SliderUInt64("Max cooldown difference", &config.max_cooldown_difference, 1, 10000, "%d", ImGuiSliderFlags_Logarithmic);
        }
    }

    void metabolismConfig(sim::MetabolismConfig & config) {
        if (ImGui::CollapsingHeader("Metabolism_Config")){
            ImGui::SliderDouble("Natural food decay per tick", &config.naturalfoodDecayPerTick, 0.0f, 1.0f);
            ImGui::SliderDouble("starving health decay", &config.starvingHealthDecayPerTick, 0.0f, 1.0f);
            ImGui::SliderDouble("Health Regen per Tick", &config.healthRegenPerTick, 0.0f, 1.0f);
            ImGui::SliderDouble("Food used to heal", &config.foodPerHealthRegenerated, 0.0f, 100.0f, "%.3f", ImGuiSliderFlags_Logarithmic);
        };
    }

    void Menu(sim::Config& config) {
        ImGui::Begin("config");
        ImGui::SliderUInt16("Age", &config.maxAge, 100, 10000, "%d", ImGuiSliderFlags_Logarithmic);
        ImGui::SliderDouble("sensors", &config.sensors.sensibility, 0.0f, 200.0f);
        nnConfig(config.neural_net);
        reproductionConfig(config.reproduction);
        metabolismConfig(config.metabolism);
        ImGui::End();
    }



}
