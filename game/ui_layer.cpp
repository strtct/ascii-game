#include "ui_layer.hpp"
#include "player.hpp"
#include "engine/ascii_renderer.hpp"
#include "engine/ui/ui_manager.hpp"
#include "ui_player_info_component.hpp"
#include "ui_log_component.hpp"
#include <string>
#include <memory>

namespace ui_layer {

	void init_components(const Player& player, const std::deque<std::string>& log_buffer) {
		
		auto playerInfoComponent = std::make_shared<PlayerInfoComponent>(0,int(ascii::HEIGHT)-8, 8, int(ascii::WIDTH), 8, player);
		
		auto logComponent = std::make_shared<LogComponent>(0,int(ascii::HEIGHT)-13, 13, int(ascii::WIDTH), 5, log_buffer);
		ui::add_component(logComponent);
		ui::add_component(playerInfoComponent);
}

	}


