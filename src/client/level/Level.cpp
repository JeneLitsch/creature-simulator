#include "Level.hpp"
#include "client/session/Session.hpp"
#include "imgui.h"
#include "render.hpp"
#include "configMenu.hpp"
#include "sim/create.hpp"

namespace client::level {

    bool showMenu = true;

	Level::Level(session::Session & session, sim::Simulation & simulation)
		: session{session}
		, simulation{simulation}
		, tick_timer{1.0/100.0} {
		
		this->camera_center = stx::position2f{this->session->get_sim().get_grid().size()} / 2.f;
	}



	void Level::update(double dt) {
		this->update_camera(dt);

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::F5)) {
			this->session->export_sim("tmp/export/sim.json");
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::F9)) {
			this->pop();
			this->pop();
			this->push(std::make_unique<session::Session>("tmp/export/sim.json"));
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::F6)) {
			this->session->get_sim().get_ecs().run_system([&] (const sim::Ecs::Entity & entity) {
				auto id = entity.get_id();
				this->session->export_entity("tmp/export/entity/" + std::to_string(id) + ".json",id);
			});
		}


		if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
			auto & ecs = this->session->get_sim().ecs;
			auto & grid = this->session->get_sim().grid;
			if(grid.in_range(this->cursor_position) && grid[this->cursor_position] == 0) {
				sim::create_barrier(ecs, stx::vector2i{this->cursor_position}, grid);
			}
		}

		if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)) {
			auto & ecs = this->session->get_sim().ecs;
			auto & grid = this->session->get_sim().grid;
			if(grid.in_range(this->cursor_position)) {
				const std::uint64_t id = grid[this->cursor_position];
				if(auto * entity = ecs.get_if(id)) {
					ecs.get(id).mark_delete();
					grid[this->cursor_position] = 0;
					ecs.clean_up();
				}
			}
		}



		this->camera_center = stx::clamp(
			this->camera_center,
			stx::position2f{0,0},
			stx::position2f{this->session->get_sim().get_grid().size()}
		);
		
		if(this->tick_timer(dt)) {
			this->session->tick();
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
	}
	

	
	void Level::render(sf::RenderTarget & render_target) {

        if (showMenu){
            level::Menu(level::Level::simulation->config);
        }

		auto old_view = render_target.getView();
		camera.setCenter(this->camera_center.to<sf::Vector2f>());
		camera.setSize(960.f * this->camera_zoom, 540.f * this->camera_zoom);
		render_target.setView(camera);

		auto & sim = this->session->get_sim();
		auto & grid = sim.get_grid();
		auto & ecs = sim.get_ecs();
		auto & field = sim.get_pheromone_field();
		
		render_phermones(render_target, field);
		render_frame(render_target, grid, ecs);
		render_grid(render_target, grid, ecs);
		render_cursor(render_target, this->cursor_position);
		
		render_target.setView(old_view);
	}



	void Level::on_event(const core::MouseMoved & event)  {
		auto x = event.window->mapPixelToCoords(event.position.to<sf::Vector2i>(), this->camera);
		this->cursor_position = stx::position2i{stx::floor(stx::position2f::from(x))};
	}


	
    void Level::on_event(const core::KeyPressed& event) {
        if (event.code == sf::Keyboard::O) {
            showMenu = !showMenu;
        }
    }


	
	void Level::init() {

	}
}
