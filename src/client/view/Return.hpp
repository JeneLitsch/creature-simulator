#pragma once
#include "stdxx/reference.hxx"
#include "client/core/GameState.hpp"
#include "View.hpp"

namespace client::view {
	class Return : public core::GameState {
	public:
		Return(stx::reference<View> view) : view{view} {}
		virtual void update(double dt) override;
		virtual void ui(stx::vector2f window_size) final;
		virtual void render(sf::RenderTarget & render_target) override;
		virtual const char * name() override { return "Return"; }
	protected:
		virtual void init() override;
		virtual void on_event(const core::KeyPressed &) override;

	private:
		stx::reference<View> view;
	};
}