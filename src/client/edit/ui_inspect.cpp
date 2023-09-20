#include "ui_inspect.hpp"
#include "imgui.h"

namespace client::edit {
	namespace {
		const char * comp_name(const sim::Stomach &) { return "Stomach"; }
		const char * comp_name(const sim::Transform &) { return "Transform"; }
		const char * comp_name(const sim::Movement &) { return "Movement"; }
		const char * comp_name(const sim::Age &) { return "Age"; }
		const char * comp_name(const sim::Reproduction &) { return "Reproduction"; }
		const char * comp_name(const sim::Edible &) { return "Edible"; }
		const char * comp_name(const sim::FoodSpawn &) { return "FoodSpawn"; }
		const char * comp_name(const sim::Sprite &) { return "Sprite"; }
		const char * comp_name(const sim::StomachSensorFB &) { return "StomachSensorFB"; }
		const char * comp_name(const sim::StomachSensorLR &) { return "StomachSensorLR"; }
		const char * comp_name(const sim::EdibleSensorFB &) { return "EdibleSensorFB"; }
		const char * comp_name(const sim::EdibleSensorLR &) { return "EdibleSensorLR"; }
		const char * comp_name(const sim::Health &) { return "Health"; }
		const char * comp_name(const sim::NeuralNetwork &) { return "NeuralNetwork"; }



		void comp_details(sim::Stomach & comp) {
			ImGui::Text("Food: %f", comp.food);
			ImGui::Text("Share Food: %s", comp.shareFood ? "Enabled" : "Disabled");
		}



		void comp_details(sim::Transform & comp) {
			ImGui::Text("Position: %d, %d", comp.location.x, comp.location.y);
			ImGui::Text("Rotation: %d, %d", comp.rotation.x, comp.rotation.y);
		}



		void comp_details(sim::Movement & comp) {
			ImGui::Text("Direction: %d, %d", comp.direction.x, comp.direction.y);
		}



		void comp_details(sim::Age & comp) {
			ImGui::Text("Ticks: %lu", comp.age);
		}


		
		void comp_details(sim::Reproduction & comp) {
			ImGui::Text("Max Cooldown: %lu", comp.max_cooldown);
			ImGui::Text("Current Cooldown: %lu", comp.current_cooldown);
			ImGui::Text("Wants to reproduce: %s", comp.wants_to_reproduce ? "Yes" : "No");
		}



		void comp_details(sim::Edible & comp) {
			ImGui::Text("Nutrition Value: %f", comp.value);
		}



		void comp_details(sim::FoodSpawn & comp) {
			ImGui::Text("Spawn Cooldown: %d", comp.spawn_cooldown);
			ImGui::Text("Spawn Counter: %d", comp.spawn_counter);
			ImGui::Text("Spawn Radius: %d", comp.spawn_radius);
		}



		void comp_details(sim::Sprite & comp) {
			ImGui::Text("Color: %d, %d, %d", comp.color.r, comp.color.g, comp.color.b);
		}



		template<typename Comp, sim::EntitySensorAxis axis>
		void comp_details(sim::EntitySensor<Comp, axis> & comp) {
			ImGui::Text("Value: %f", comp.value);
		}



		void comp_details(sim::Health & comp) {
			ImGui::Text("Health Points: %f", comp.currentHealth);
		}




		void comp_details(sim::NeuralNetwork & comp) {

		}
		


		template<typename Comp>
		void ui_inspect_component(sim::Ecs::Entity & entity) {
			if(auto * comp = entity.get_if<Comp>()) {
		        if (ImGui::CollapsingHeader(comp_name(*comp))){
					comp_details(*comp);
				}
			}
		}
	}



	void ui_inspect(sim::Ecs::Entity & entity) {
		ImGui::Begin("Inspector");
		ImGui::Text("Entity #%lu", entity.get_id());

		ui_inspect_component<sim::Stomach>(entity);
		ui_inspect_component<sim::Transform>(entity);
		ui_inspect_component<sim::Movement>(entity);
		ui_inspect_component<sim::Age>(entity);
		ui_inspect_component<sim::Reproduction>(entity);
		ui_inspect_component<sim::Edible>(entity);
		ui_inspect_component<sim::FoodSpawn>(entity);
		ui_inspect_component<sim::Sprite>(entity);

		ui_inspect_component<sim::StomachSensorFB>(entity);
		ui_inspect_component<sim::StomachSensorLR>(entity);
		ui_inspect_component<sim::EdibleSensorFB>(entity);
		ui_inspect_component<sim::EdibleSensorLR>(entity);

		ui_inspect_component<sim::Health>(entity);
		ui_inspect_component<sim::NeuralNetwork>(entity);

		ImGui::End();
	}
}