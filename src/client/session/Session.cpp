#include "Session.hpp"
#include "client/view/View.hpp"
#include "sim/export.hpp"
#include "sim/import.hpp"
#include <fstream>

namespace client::session {
	Session::Session(const sim::WorldPreset & preset, const sim::Config & config) {
		this->simulation = sim::Simulation::generate(preset);
		this->simulation->config = config;
	}



	Session::Session(const std::filesystem::path & path) {
		stx::json::node json = stx::json::from_file(path);
		this->simulation = sim::import_simulation(json);
	}



	void Session::update(double dt) {
		this->push(std::make_unique<view::View>(*this, *this->simulation));
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


	
	sim::Simulation & Session::get_sim() {
		return *this->simulation;
	}
}