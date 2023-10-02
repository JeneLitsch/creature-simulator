#pragma once
#include <random>
#include "Sub.hpp"
#include "xoshiro256.h"
#include "sim/WorldPreset.hpp"
#include "sim/Simulation.hpp"

namespace client::main_menu {
	class Main;
	class New : public Sub {
	public:
		New(stx::reference<Main> main);

		virtual void update(double dt) override;
		virtual void render(sf::RenderTarget & render_target) override;
		virtual const char * name() override { return "New"; }

	protected:
		virtual void init() override {}
		virtual void ui_content() override;
	private:
		void generate();

		sim::WorldPreset preset;
		sim::Config config;

		Xoshiro::Xoshiro256PP rng;

		int radio_index = 0;
	};
}
