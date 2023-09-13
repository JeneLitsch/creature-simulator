#include "New.hpp"
#include "Main.hpp"
#include "imgui.h"
#include "client/session/Session.hpp"

namespace client::main_menu {
	struct DefaultSize {
		const char * name;
		stx::size2u32 size;
	};

	const auto default_sizes = std::array{
		DefaultSize{ "16 x 16", {16, 16}, },
		DefaultSize{ "32 x 32", {32, 32}, },
		DefaultSize{ "64 x 64", {64, 64}, },
		DefaultSize{ "128 x 128",  {128, 128} },
		DefaultSize{ "256 x 256",  {256, 256} },
		DefaultSize{ "512 x 512",  {512, 512} },
	};


	New::New(stx::reference<Main> main)
		: Sub{main} {

		this->set_title("New Simulation");
	}



	void New::update(double dt) {
	}




	void New::ui_content() {
		ImGui::InputUInt64("Seed", &this->preset.seed, 1, 100, ImGuiInputTextFlags_CharsHexadecimal);
		if(ImGui::Button("Randomize")) { 
			this->preset.seed = rng();
		}
		if(ImGui::InputUInt32("Width", &this->preset.size.x, 1, 16)) {
			this->preset.size.x = std::clamp<std::uint32_t>(this->preset.size.x, 8, 1024);
		}
		if(ImGui::InputUInt32("Height", &this->preset.size.y, 1, 16)) {
			this->preset.size.x = std::clamp<std::uint32_t>(this->preset.size.y, 8, 1024);
		}

		ImGui::BeginGroup();

		for(const auto & default_size : default_sizes) {
			if(ImGui::Button(default_size.name)) {
				this->preset.size = default_size.size;
			}
			ImGui::SameLine();
		}

		ImGui::EndGroup();

		ImGui::Text("Total Cells %lld", this->preset.size.x * this->preset.size.y);

		ImGui::NewLine();

		ImGui::SetWindowFontScale(2);

		if(ImGui::Button("Generate")) {
			this->generate();
		}

		ImGui::SetWindowFontScale(1);
	}



	void New::generate() {
		this->pop();
		this->pop();
		this->push(std::make_unique<session::Session>(this->preset));
	}



	void New::render(sf::RenderTarget & render_target) {

	}
}