#pragma once
#include <vector>
#include <optional>
#include "stdxx/reference.hxx"
#include "client/core/GameState.hpp"
#include "tool/Tool.hpp"

namespace client::session {
	class Session;
}

namespace client::view {
	class View;
}

namespace client::edit {
	class Edit : public core::GameState {
	public:
		Edit(stx::reference<view::View> view);
		virtual void ui(stx::vector2f window_size) final;
		virtual void update(double dt) override;
		virtual void render(sf::RenderTarget & render_target) override;
		virtual const char * name() override { return "Edit"; }

		void inspect(std::uint64_t id);
	private:
		virtual void on_event(const core::MouseMoved &) override;
		virtual void on_event(const core::KeyPressed &) override;
		virtual void on_event(const core::MouseButtonPressed &) override;
		virtual void on_event(const core::MouseButtonReleased &) override;
		virtual void init() override;

		stx::reference<view::View> view;
		stx::reference<session::Session> session;
		stx::position2i cursor_position;

		std::vector<Tool> tools;
		stx::optref<Tool> current_tool;

		std::uint64_t inspected_id = 0;

		bool is_drawing = false;

		sf::RenderTexture neural_network_graph;
	};
}