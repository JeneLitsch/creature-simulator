#include "View.hpp"
#include "client/session/Session.hpp"
#include "imgui.h"
#include "render.hpp"
#include "configMenu.hpp"
#include "sim/create.hpp"
#include "client/edit/Edit.hpp"
#include "client/file/File.hpp"
#include "client/file/SaveFile.hpp"
#include "client/file/OpenFile.hpp"
#include "Return.hpp"

namespace client::view {

	View::View(session::Session & session, sim::Simulation & simulation)
		: session{session}
		, tick_timer{tick_speed} 
		, simulation{simulation} {
		
		this->camera_center = stx::position2f{this->session->get_sim().get_grid().size()} / 2.f;
	}



	void View::ui(stx::vector2f window_size) {
        if (showMenu){
			this->ui_config();
        }
	}



	void View::ui_config() {
		view::Menu(tick_speed, simulation->config);
	}



	void View::update(double dt) {
		this->update_camera(dt);

		if(this->tick_timer(dt)) {
			this->session->tick();
		}
	}



	void View::update_camera(double dt) {
		const float dt_f = static_cast<float>(dt);
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			this->camera_center.x -= dt_f * camera_speed * this->camera_zoom;
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			this->camera_center.x += dt_f * camera_speed * this->camera_zoom;
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			this->camera_center.y -= dt_f * camera_speed * this->camera_zoom;
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			this->camera_center.y += dt_f * camera_speed * this->camera_zoom;
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
			this->camera_zoom -= this->camera_zoom * dt_f;
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
			this->camera_zoom += this->camera_zoom * dt_f;
		}

		this->camera_center = stx::clamp(
			this->camera_center,
			stx::position2f{0,0},
			stx::position2f{this->session->get_sim().get_grid().size()}
		);
	}
	

	
	void View::render(sf::RenderTarget & render_target) {

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


	
    void View::on_event(const core::KeyPressed& event) {
        if (event.code == sf::Keyboard::Tab) {
            showMenu = !showMenu;
        }

		if (event.code == sf::Keyboard::Escape) {
			this->push(std::make_unique<Return>(*this));
        }

		if(event.code == sf::Keyboard::Space) {
			this->push(std::make_unique<edit::Edit>(*this));
		}

        if (event.code == sf::Keyboard::S && event.control) {
			this->push(std::make_unique<file::SaveFile>(std::filesystem::path{"."}, [this] (auto path) {
				this->pop();
				this->session->export_sim(path);
			}));
        }

        if (event.code == sf::Keyboard::O && event.control) {
			this->push(std::make_unique<file::OpenFile>(std::filesystem::path{"."}, [this] (auto path) {
				this->pop();
				this->pop();
				this->pop();
				this->push(std::make_unique<session::Session>(path));
			}));
        }

    }


	
	void View::init() {

	}
}
