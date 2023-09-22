#include "File.hpp"
#include "imgui.h"
#include <fstream>

namespace client::file {
	File::File(std::filesystem::path path, std::function<void(std::filesystem::path)> callback) : path{std::filesystem::canonical(path)}, callback{callback} {
		this->new_file_name.fill('\0');
	}



	void File::ui(stx::vector2f window_size) {
		ImGui::Begin("Edit", nullptr
			, ImGuiWindowFlags_NoBackground
			| ImGuiWindowFlags_NoTitleBar
			| ImGuiWindowFlags_NoResize
			| ImGuiWindowFlags_NoMove
			| ImGuiWindowFlags_NoNavFocus
			| ImGuiWindowFlags_NoBringToFrontOnFocus);

		ImGui::SetWindowSize(window_size.to<ImVec2>());
		ImGui::SetWindowPos({0,0});

		ImGui::SetWindowFontScale(2);
		ImGui::Text("%s", path.c_str());
		ImGui::SetWindowFontScale(1);

		std::filesystem::path next_path = this->path;

		if(ImGui::Button("..")) {
			next_path = path.parent_path();
		}

		ImGui::Separator();

		for(auto & member : std::filesystem::directory_iterator(this->path)) {
			auto & member_path = member.path();
			if(member.is_directory()) {
				if(ImGui::Button(member_path.filename().c_str())) {
					next_path = member_path;
				}
			}
		}

		ImGui::Separator();

		for(auto & member : std::filesystem::directory_iterator(this->path)) {
			auto & member_path = member.path();
			if(member.is_regular_file()) {
				if(ImGui::Button(member_path.filename().c_str())) {
					this->callback(member_path);
				}
			}
		}

		this->path = next_path;

		ImGui::NewLine();
		ImGui::Separator();
		ImGui::NewLine();

		ImGui::InputText("Name", this->new_file_name.data(), 64);
		
		if(ImGui::Button("create file")) {
			std::ofstream ofs{this->path / this->new_file_name.data()};
		}
		
		if(ImGui::Button("create directory")) {
			std::filesystem::create_directories(this->path / this->new_file_name.data());
		}

		ImGui::End();
	}



	void File::update(double dt) {

	}



	void File::render(sf::RenderTarget & render_target) {

	}


	void File::on_event(const core::KeyPressed & event)  {
		if(event.code == sf::Keyboard::Escape) {
			this->pop();
		}
	}
}