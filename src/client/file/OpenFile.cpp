#include "OpenFile.hpp"
#include "imgui.h"
#include <fstream>

namespace client::file {
	OpenFile::OpenFile(std::filesystem::path path, std::function<void(std::filesystem::path)> callback) : File{path, callback} {}
	void OpenFile::ui_addtional() {}
	void OpenFile::ui_header() {
		ImGui::Text("Import");
	}
}