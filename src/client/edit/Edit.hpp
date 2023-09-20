#pragma once
#include <vector>
#include <optional>
#include "stdxx/reference.hxx"
#include "client/core/GameState.hpp"
#include "tool/Tool.hpp"

namespace client::session {
	class Session;
}

namespace client::level {
	class Level;
}

namespace client::edit {
	class Edit : public core::GameState {
	public:
		Edit(stx::reference<level::Level> level);
		virtual void ui(stx::vector2f window_size) final;
		virtual void update(double dt) override;
		virtual void render(sf::RenderTarget & render_target) override;
		virtual const char * name() { return "Edit"; }

		void inspect(std::uint64_t id);
	private:
		virtual void on_event(const core::MouseMoved &) override;
		virtual void on_event(const core::KeyPressed &) override;
		virtual void init() override;

		stx::reference<level::Level> level;
		stx::reference<session::Session> session;
		stx::position2i cursor_position;

		std::vector<Tool> tools;
		stx::optref<Tool> current_tool;

		std::uint64_t inspected_id = 0;
	};
}