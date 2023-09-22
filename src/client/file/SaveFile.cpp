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

		if(ImGui::InputText("Name", this->new_file_name.data(), 64, ImGuiInputTextFlags_EnterReturnsTrue)) {
			std::ofstream ofs{this->path / this->new_file_name.data()};
			this->callback(this->path / this->new_file_name.data());
		}
		
		if(ImGui::Button("Save new file")) {
			std::ofstream ofs{this->path / this->new_file_name.data()};
			this->callback(this->path / this->new_file_name.data());
		}
		
		if(ImGui::Button("Create directory")) {
			std::filesystem::create_directories(this->path / this->new_file_name.data());
		}
	}



	void SaveFile::ui_header() {
		ImGui::Text("Export");
	}
}