#include "File.hpp"
#include "imgui.h"
#include <fstream>

namespace client::file {
	File::File(std::filesystem::path path, std::function<void(std::filesystem::path)> callback) : path{std::filesystem::canonical(path)}, callback{callback} {
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
		ImGui::SetWindowPos({64,0});

		ImGui::SetWindowFontScale(2);
		this->ui_header();
		ImGui::SetWindowFontScale(1);

		std::filesystem::path next_path = this->path;

		std::filesystem::path back_path;

		for(const auto & sub_path : this->path) {
			back_path /= sub_path; 
			if(ImGui::Button(sub_path.string().c_str())) {
				next_path = back_path;
			}
			ImGui::SameLine();
			ImGui::Text("/");
			ImGui::SameLine();
		}

		ImGui::NewLine();


		for(char letter : "ABCDEFGHIJKLMNOPQRSTUVWXYZ") {
			std::filesystem::path root_path = letter + std::string(":\\");
			if(std::filesystem::exists(root_path)) {
				if(ImGui::Button(root_path.string().c_str())) {
					next_path = root_path;
				}
				ImGui::SameLine();
			}
		}

		ImGui::SeparatorText("Directories");

		if(ImGui::Button("..")) {
			next_path = path.parent_path();
		}

		for(auto & member : std::filesystem::directory_iterator(this->path)) {
			auto & member_path = member.path();
			if(member.is_directory()) {
				if(ImGui::Button(member_path.filename().string().c_str())) {
					next_path = member_path;
				}
			}
		}

		ImGui::SeparatorText("Files");

		for(auto & member : std::filesystem::directory_iterator(this->path)) {
			auto & member_path = member.path();
			if(member.is_regular_file()) {
				if(ImGui::Button(member_path.filename().string().c_str())) {
					this->callback(member_path);
				}
			}
		}

		this->path = next_path;

		this->ui_addtional();

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