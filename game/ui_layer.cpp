#include "ui_layer.hpp"
#include "player.hpp"
#include "engine/ascii_renderer.hpp"
#include "engine/ui/ui_manager.hpp"
#include "ui_player_info_component.hpp"
#include "ui_log_component.hpp"
#include <string>
#include <memory>
#include "ui_render_area.hpp"
#include "ui_crosshair_component.hpp"

namespace ui_layer {
	std::shared_ptr<RenderAreaComponent> renderArea;
	void init_components(const Player& player, const std::deque<std::string>& log_buffer, const GameWorld& world) {
		
		renderArea = std::make_shared<RenderAreaComponent>(
			0, 0, int(ascii::WIDTH), int(ascii::HEIGHT) - 13, 0,
			int(ascii::HEIGHT)
		);

		auto playerInfoComponent = std::make_shared<PlayerInfoComponent>(
			0,int(ascii::HEIGHT)-8, int(ascii::WIDTH), 8, 0, 8, player
		);
		
		auto logComponent = std::make_shared<LogComponent>(
			0,int(ascii::HEIGHT)-13, int(ascii::WIDTH), 5, 0, 13, log_buffer
		);
		auto crosshair = std::make_shared<CrosshairComponent>(
			player.getPosition().x + player.getFacingDirection().x,
			player.getPosition().y + player.getFacingDirection().y,
			1, 1, 4, 0, player, world
		);
		ui::add_component(renderArea);
		ui::add_component(logComponent);
		ui::add_component(playerInfoComponent);
		ui::add_component(crosshair);
		

	}
	Rect get_render_area_component() {
    	return renderArea->getBounds();
	}

}

