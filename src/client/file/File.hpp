#pragma once
#include <filesystem>
#include <array>
#include <functional>
#include "client/core/GameState.hpp"

namespace client::file {
	class File : public core::GameState {
	public:
		File(std::filesystem::path path, std::function<void(std::filesystem::path)>  callback);
		virtual void ui(stx::vector2f window_size) final;
		virtual void update(double dt) override;
		virtual void render(sf::RenderTarget & render_target) override;
		virtual const char * name() override { return "File"; }
		virtual void on_event(const core::KeyPressed &) override;
	protected:
		virtual void init() override {}
		virtual void ui_addtional() {}
		virtual void ui_header() {}
		std::filesystem::path path;
		std::function<void(std::filesystem::path)> callback;
	};
}