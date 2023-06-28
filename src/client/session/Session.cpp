#include "Session.hpp"
#include "client/level/Level.hpp"
#include "sim/export.hxx"

namespace client::session {
	Session::Session () {
		this->simulation = std::make_unique<sim::Simulation>();
	}



	void Session::update(double dt) {
		this->push(std::make_unique<level::Level>(*this));
	}
	
	
	
	void Session::render(sf::RenderTarget & render_target) {

	}



	void Session::tick() {
		this->simulation->tick();
	}



	void Session::export_entity(const std::filesystem::path & path, std::uint64_t id) const {
		std::ofstream ofs{path};
		std::filesystem::create_directories(path.parent_path());
		auto json = sim::export_entity(simulation->get_ecs().get(id));
		auto formatted = stx::json::format(json, stx::json::pretty);
		ofs << formatted;
	}



	void Session::export_sim(const std::filesystem::path & path) const {
		std::ofstream ofs{path};
		std::filesystem::create_directories(path.parent_path());
		auto json = sim::export_sim(*simulation);
		auto formatted = stx::json::format(json, stx::json::pretty);
		ofs << formatted;
	}



	const sim::Simulation & Session::get_sim() const {
		return *this->simulation;
	}
}