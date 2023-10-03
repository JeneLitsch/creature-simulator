#pragma once
#include "stdxx/reference.hxx"
#include "client/core/GameState.hpp"

namespace client::main_menu {
	class Main;
	class Sub : public core::GameState {
	public:
		Sub(stx::reference<Main> main);

		virtual void update(double dt) override;
		virtual void ui(stx::vector2f window_size) final;
		virtual void render(sf::RenderTarget & render_target) override;

		virtual ~Sub();

	protected:
		virtual void ui_content() = 0;
		virtual void init() override {}

		void set_title(std::string str);
	private:
		stx::reference<Main> main;
		std::string title = " ";
	};
}