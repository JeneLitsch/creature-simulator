#include "Level.hpp"
#include "render_entity.hpp"
#include "move_randomly.hpp"
#include "client/session/Session.hpp"

namespace client::level {
	void init_entities(Ecs & ecs, auto & rng) {
		std::uniform_real_distribution<float> dist_x{0, 960};
		std::uniform_real_distribution<float> dist_y{0, 540};
		std::uniform_real_distribution<float> dist_rot{0, 360};
		for(std::size_t i = 0; i < 100; ++i) {
			auto & entity = ecs.new_entity();
			entity.add(Sprite{
				.tex_position = {0,0},
				.tex_size = {16,32},
			});
			entity.add(Rotation{
				.angle = dist_rot(rng)
			});
			entity.add(Position{
				.position = stx::position2f{dist_x(rng), dist_y(rng)}
			});
		}
	}



	Level::Level(session::Session & session) : session{session} {
	}



	void Level::update(double dt) {
		this->session.send_request(net::FetchUpdate {
			.simulation_step = this->simulation_step
		});
		this->ecs.run_system([&] (auto & entity) {
			return move_randomly(entity, dt, this->rng);
		});
		while(auto reponse = this->session.fetch_response()) {
			std::visit([&] (auto & r) { 
				this->handle_response(r);
			}, *reponse);
		}
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
		this->rng.seed(42);
		init_entities(this->ecs, this->rng);
		creature_texture.loadFromFile("assets/creatures.png");
		this->session.send_request(net::Register{
			.name = "Bobby DropTable"
		});
	}


	void Level::handle_response(const net::InitState & response) {
		std::cout << "Got InitState at step " << response.simulation_step << "\n";
		this->simulation_step = response.simulation_step;
	}


	void Level::handle_response(const net::UpdateState & response) {
		std::cout << "Got update at step " << response.simulation_step << "\n";
		this->simulation_step = response.simulation_step;
	}
}
