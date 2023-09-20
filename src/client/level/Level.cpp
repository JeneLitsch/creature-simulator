#include "Level.hpp"
#include "client/session/Session.hpp"
#include "imgui.h"
#include "render.hpp"
#include "configMenu.hpp"
#include "sim/create.hpp"
#include "client/edit/Edit.hpp"

namespace client::level {

	Level::Level(session::Session & session, sim::Simulation & simulation)
		: session{session}
		, simulation{simulation}
		, tick_timer{tick_speed} {
		
		this->camera_center = stx::position2f{this->session->get_sim().get_grid().size()} / 2.f;
	}



	void Level::ui(stx::vector2f window_size) {
        if (showMenu){
			this->ui_config();
        }
	}



	void Level::ui_config() {
		level::Menu(tick_speed, simulation->config);
	}



	void Level::update(double dt) {
		this->update_camera(dt);

		this->lag += dt;

		const double tick_dt = 1.0 / static_cast<double>(tick_speed);
		while(this->lag >= tick_dt) {
			this->session->tick();
			this->lag -= tick_dt;
		}
	}



	void Level::update_camera(double dt) {
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

		this->camera_center = stx::clamp(
			this->camera_center,
			stx::position2f{0,0},
			stx::position2f{this->session->get_sim().get_grid().size()}
		);
	}
	

	
	void Level::render(sf::RenderTarget & render_target) {

		auto old_view = render_target.getView();
		camera.setCenter(this->camera_center.to<sf::Vector2f>());
		camera.setSize(960.f * this->camera_zoom, 540.f * this->camera_zoom);
		render_target.setView(camera);

		auto & sim = this->session->get_sim();
		auto & grid = sim.get_grid();
		auto & ecs = sim.get_ecs();
		
		render_frame(render_target, grid, ecs);
		render_grid(render_target, grid, ecs);
		
		render_target.setView(old_view);
	}


	
    void Level::on_event(const core::KeyPressed& event) {
        if (event.code == sf::Keyboard::O) {
            showMenu = !showMenu;
        }

		if(event.code == sf::Keyboard::Space) {
			this->push(std::make_unique<edit::Edit>(*this));
		}
        if (event.code == sf::Keyboard::F5) {
			this->session->export_sim("tmp/export/sim.json");
        }
        if (event.code == sf::Keyboard::F6) {
			this->session->get_sim().get_ecs().run_system([&] (const sim::Ecs::Entity & entity) {
				auto id = entity.get_id();
				this->session->export_entity("tmp/export/entity/" + std::to_string(id) + ".json",id);
			});
        }
        if (event.code == sf::Keyboard::F9) {
			this->pop();
			this->pop();
			this->push(std::make_unique<session::Session>("tmp/export/sim.json"));
        }

    }


	
	void Level::init() {

	}
}
