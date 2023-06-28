#pragma once
#include <future>
#include "stdxx/chrono.hxx"
#include "sim/Simulation.hpp"
#include "client/core/GameState.hpp"

namespace client::session {
	class Session : public core::GameState{
	public:
		Session ();
		void update(double dt) override;
		void render(sf::RenderTarget & render_target) override;
		virtual ~Session () = default;

		void export_entity(const std::filesystem::path & path, std::uint64_t id) const;
		void export_sim(const std::filesystem::path & path) const;

	protected:
		virtual void init() override {}
	private:
		sim::Simulation simulation;
	};
}