#include "Level.hpp"
#include "client/session/Session.hpp"
#include "render.hpp"

namespace client::level {
	Level::Level(session::Session & session, sim::Simulation & simulation)
		: session{session}
		, simulation{simulation}
		, tick_timer{1.0/10.0} {
		
		this->camera_center = stx::position2f{this->simulation->get_grid().size()} / 2.f;
	}



	void Level::update(double dt) {
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			this->camera_center.x -= (dt * camera_speed) * this->camera_zoom;
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			this->camera_center.x += dt * camera_speed * this->camera_zoom;
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			this->camera_center.y -= dt * camera_speed * this->camera_zoom;
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			this->camera_center.y += dt * camera_speed * this->camera_zoom;
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
			this->camera_zoom -= this->camera_zoom * dt;
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
			this->camera_zoom += this->camera_zoom * dt;
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::F5)) {
			this->session->export_sim("tmp/export/sim.json");
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::F5)) {

		}

		this->camera_center = stx::clamp(
			this->camera_center,
			stx::position2f{0,0},
			stx::position2f{this->simulation->get_grid().size()}
		);
		
		if(this->tick_timer(dt)) {
			this->simulation->tick();
		}
	}
	
	
	
	void Level::render(sf::RenderTarget & render_target) {
		auto old_view = render_target.getView();
		auto new_view = render_target.getView();
		new_view.setCenter(this->camera_center.to<sf::Vector2f>());
		new_view.setSize(960.f * this->camera_zoom, 540.f * this->camera_zoom);
		render_target.setView(new_view);
		
		render_phermones(render_target, this->simulation->get_pheromone_field());
		render_frame(render_target, this->simulation->get_grid(), this->simulation->get_ecs());
		render_grid(render_target, this->simulation->get_grid(), this->simulation->get_ecs());
		
		render_target.setView(old_view);
	}
	
	
	
	void Level::init() {

	}
}
