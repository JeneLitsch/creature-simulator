#pragma once
#include <filesystem>
#include <array>
#include <functional>
#include "client/core/GameState.hpp"
#include "File.hpp"

namespace client::file {
	class OpenFile : public File {
	public:
		OpenFile(std::filesystem::path path, std::function<void(std::filesystem::path)>  callback);
	protected:
		virtual void ui_addtional() override;
		virtual void ui_header() override;
	};
}