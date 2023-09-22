#pragma once
#include <filesystem>
#include <array>
#include <functional>
#include "client/core/GameState.hpp"
#include "File.hpp"

namespace client::file {
	class SaveFile : public File {
	public:
		SaveFile(std::filesystem::path path, std::function<void(std::filesystem::path)>  callback);
	protected:
		virtual void ui_addtional() override;
	};
}