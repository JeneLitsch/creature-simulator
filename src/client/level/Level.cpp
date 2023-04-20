#include "Level.hpp"
#include "render_entity.hpp"
#include "client/session/Session.hpp"

namespace client::level {

	Level::Level(session::Session & session) : session{session} {}



	void Level::update(double dt) {
		this->session.send_request(net::FetchUpdate{});

		while(auto reponse = this->session.fetch_response()) {
			std::visit([&] (auto & r) { 
				this->handle_response(r);
			}, *reponse);
		}

		ecs.run_system([dt, this] (Ecs::Entity & entity) {
			if(entity.has<Position>()) {
				auto & pos = entity.get<Position>();
				pos.t += dt * static_cast<float>(this->tps);
			}
		});

		ecs.run_system([dt, this] (Ecs::Entity & entity) {
			if(entity.has<Rotation>()) {
				auto & rot = entity.get<Rotation>();
				rot.t += dt * static_cast<float>(this->tps);
			}
		});
	}
	
	
	
	void Level::render(sf::RenderTarget & render_target) {
		sf::VertexArray vertecies;
		vertecies.setPrimitiveType(sf::Quads);
		this->ecs.run_system([&] (auto & entity) {
			return render_entity(entity, vertecies);
		});
		render_target.draw(vertecies, sf::RenderStates {
			sf::BlendAlpha,
			sf::Transform::Identity,
			&this->creature_texture,
			nullptr
		});
	}
	
	
	
	void Level::init() {

		creature_texture.loadFromFile("assets/creatures.png");
		this->session.send_request(net::Register{
			.name = "Bobby DropTable"
		});
	}


	void Level::handle_response(const net::InitState & response) {
		this->tps = response.tps;
		for(const auto id : response.entities) {
			auto & entity = ecs.new_entity();
			entity.add(Sprite{
				.tex_position = {0,0},
				.tex_size = {16,32},
			});
		}
		for(const auto & [id, position] : response.positions) {
			ecs.get(id).add(Position{
				.prev = position,
				.next = position,
				.t = 0.f
			});
		}
		for(const auto & [id, angle] : response.rotations) {
			ecs.get(id).add(Rotation{
				.prev = 0.f,
				.next = 0.f,
				.t = 0.f
			});
		}
	}


	void Level::handle_response(const net::UpdateState & response) {
		for(const auto & [id, position] : response.positions) {
			auto & pos = ecs.get(id).get<Position>();
			pos.prev = pos.next;
			pos.next = position;
			pos.t = 0.f;
		}
		for(const auto & [id, angle] : response.rotations) {
			auto & rot = ecs.get(id).get<Rotation>();
			rot.prev = rot.next;
			rot.next = angle;
			rot.t = 0.f;
		}
	}
}
