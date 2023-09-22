#include "SaveFile.hpp"
#include "imgui.h"
#include <fstream>

namespace client::file {
	SaveFile::SaveFile(std::filesystem::path path, std::function<void(std::filesystem::path)> callback) : File{path, callback} {
		this->new_file_name.fill('\0');
	}



	void SaveFile::ui_addtional() {
		ImGui::NewLine();
		ImGui::Separator();
		ImGui::NewLine();

		ImGui::InputText("Name", this->new_file_name.data(), 64);
		
		if(ImGui::Button("save new file")) {
			std::ofstream ofs{this->path / this->new_file_name.data()};
			this->callback(this->path / this->new_file_name.data());
		}
		
		if(ImGui::Button("create directory")) {
			std::filesystem::create_directories(this->path / this->new_file_name.data());
		}
	}
}