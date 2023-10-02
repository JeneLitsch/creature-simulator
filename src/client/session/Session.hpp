#pragma once
#include <future>
#include "stdxx/chrono.hxx"
#include "sim/Simulation.hpp"
#include "client/core/GameState.hpp"

namespace client::session {
	class Session : public core::GameState{
	public:
		Session (const sim::WorldPreset & preset, const sim::Config & config);
		Session (const std::filesystem::path & path);
		void update(double dt) override;
		void render(sf::RenderTarget & render_target) override;
		virtual ~Session () = default;

		void export_entity(const std::filesystem::path & path, std::uint64_t id) const;
		void export_sim(const std::filesystem::path & path) const;

		void tick();

		const sim::Simulation & get_sim() const;
		sim::Simulation & get_sim();

		virtual const char * name() override { return "Session"; }

	protected:
		virtual void init() override {}
	private:
		std::unique_ptr<sim::Simulation> simulation;
	};
}