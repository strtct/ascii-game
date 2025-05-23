#include "ui_layer.hpp"
#include "player.hpp"
#include "engine/ascii_renderer.hpp"
#include "engine/ui/ui_manager.hpp"
#include "ui_player_info_component.hpp"
#include "ui_log_component.hpp"
#include <string>
#include <memory>
#include "ui_render_area.hpp"

namespace ui_layer {
	std::shared_ptr<RenderAreaComponent> renderArea;
	void init_components(const Player& player, const std::deque<std::string>& log_buffer) {
		
		renderArea = std::make_shared<RenderAreaComponent>(
			0, 0, int(ascii::HEIGHT), int(ascii::WIDTH), int(ascii::HEIGHT) - 13
		);

		auto playerInfoComponent = std::make_shared<PlayerInfoComponent>(
			0,int(ascii::HEIGHT)-8, 8, int(ascii::WIDTH), 8, player
		);
		
		auto logComponent = std::make_shared<LogComponent>(
			0,int(ascii::HEIGHT)-13, 13, int(ascii::WIDTH), 5, log_buffer
		);
		ui::add_component(renderArea);
		ui::add_component(logComponent);
		ui::add_component(playerInfoComponent);

		

	}
	Rect get_render_area_component() {
    	return renderArea->getBounds();
	}

}

