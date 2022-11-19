#pragma once
#include <memory>
#include <vector>
#include <tuple>
#include <bitset>

namespace shared::core::ecs {
	template<typename ... Components>
	class Entity {	
	public:
		template<typename Component>
		void add(Component component) {
			this->at<Component>() = std::make_unique<Component>(component);
		}



		template<typename Component>
		void remove(Component) {
			this->at<Component>().reset();
		}



		template<typename Component>
		Component & get() {
			return *this->at<Component>();
		}



		template<typename Component>
		bool has() {
			return static_cast<bool>(this->at<Component>());
		}



		void mark_delete() {
			this->to_be_deleted = true;
		}



		bool is_marked_delete() const {
			return this->to_be_deleted;
		}

	private:
		bool to_be_deleted = false;

		template<typename Component>
		std::unique_ptr<Component> & at() {
			return std::get<std::unique_ptr<Component>>(this->components);
		}
	
		std::tuple<std::unique_ptr<Components>...> components;
		std::bitset<sizeof...(Components)> signature;
	};



	template<typename ... Components>
	class Ecs {
	public:
		using Entity = core::ecs::Entity<Components...>;

		Entity & new_entity() {
			this->entities.push_back(std::make_unique<Entity>());
			return *this->entities.back();
		}


		void clean_up() {
			auto to_be_deleted = std::remove_if(
				std::begin(entities),
				std::end(entities),
				[] (auto & entity) { return entity->is_marked_delete(); }
			);

			this->entities.erase(to_be_deleted, std::end(entities));
		}



		void run_system(auto & system) {
			for(auto & entity : this->entities) {
				system(*entity);
			}
		}
	private:
		std::vector<std::unique_ptr<Entity>> entities;
	};
}