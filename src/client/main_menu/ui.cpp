#include "ui.hpp"
#include "imgui.h"

namespace client::main_menu {
	struct DefaultSize {
		const char * name;
		stx::size2u32 size;
	};

	const auto default_sizes = std::array{
		DefaultSize{ "16 x 16", {16, 16}, },
		DefaultSize{ "32 x 32", {32, 32}, },
		DefaultSize{ "64 x 64", {64, 64}, },
		DefaultSize{ "128 x 128",  {128, 128} },
		DefaultSize{ "256 x 256",  {256, 256} },
		DefaultSize{ "512 x 512",  {512, 512} },
	};



	void ui_world(sim::WorldPreset & preset, Xoshiro::Xoshiro256PP & rng) {
		ImGui::SeparatorText("World");
		
		ImGui::InputUInt64("Seed", &preset.seed, 1, 100, ImGuiInputTextFlags_CharsHexadecimal);
		if(ImGui::Button("Randomize")) { 
			preset.seed = rng();
		}

		ImGui::BeginGroup();

		if(ImGui::InputUInt32("Width", &preset.size.x, 1, 16)) {
			preset.size.x = std::clamp<std::uint32_t>(preset.size.x, 8, 1024);
		}

		if(ImGui::InputUInt32("Height", &preset.size.y, 1, 16)) {
			preset.size.x = std::clamp<std::uint32_t>(preset.size.y, 8, 1024);
		}

		ImGui::EndGroup();

		ImGui::BeginGroup();

		for(const auto & default_size : default_sizes) {
			if(ImGui::Button(default_size.name)) {
				preset.size = default_size.size;
			}
			ImGui::SameLine();
		}

		ImGui::EndGroup();

		ImGui::Text("Total Cells %lld", preset.size.x * preset.size.y);
	}



	void ui_entities(sim::WorldPreset & preset) {
		ImGui::SeparatorText("Entities");

		if(ImGui::InputUInt32("Food Spawners", &preset.entities.food_spawners, 1, 16)) {
			preset.entities.food_spawners = std::clamp<std::uint32_t>(preset.entities.food_spawners, 8, 1024);
		}
		if(ImGui::InputUInt32("Empty Creatures", &preset.entities.empty_creatures, 1, 16)) {
			preset.entities.empty_creatures = std::clamp<std::uint32_t>(preset.entities.empty_creatures, 8, 1024);
		}
	}



	namespace {
		void ui_obstacle_policy(sim::ObstaclePreset::None) {}



		void ui_obstacle_policy(sim::ObstaclePreset::Rocks & rocks) {
			if(ImGui::InputUInt32("Cores", &rocks.cores, 1, 16)) {
				rocks.cores = std::clamp<std::uint32_t>(rocks.cores, 1, 256);
			}
			if(ImGui::InputUInt32("Build Up", &rocks.build_up, 1, 16)) {
				rocks.build_up = std::clamp<std::uint32_t>(rocks.build_up, 1, 256);
			}
		}
	}



	void ui_obstacles(sim::ObstaclePreset & preset, int & radio_index) {
		ImGui::SeparatorText("Obstacles");
		if(ImGui::RadioButton("None", &radio_index, 0)) {
			preset.policy = sim::ObstaclePreset::None{};
		}

		ImGui::SameLine();
		
		if(ImGui::RadioButton("Rocks", &radio_index, 1)) {
			preset.policy = sim::ObstaclePreset::Rocks{};
		}

		std::visit([] (auto & policy) { return ui_obstacle_policy(policy); }, preset.policy);
	}
}
