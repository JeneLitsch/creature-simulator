#include "calc_margin.hpp"
#include "SFML/Graphics.hpp"

namespace client::main_menu {
	stx::vector2f calc_margin() {
		const auto & video_modes = sf::VideoMode::getFullscreenModes();
		const float margin_scale 
			= std::empty(video_modes)
			? 1.f
			: static_cast<float>(video_modes[0].height) / 1080.0f;
			
		const stx::vector2f margin {32.f * margin_scale, 32.f * margin_scale};
		return margin;
	}
}