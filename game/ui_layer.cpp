#include "ui_layer.hpp"
#include "player.hpp"
#include "engine/ascii_renderer.hpp"
#include "engine/ui/ui_manager.hpp"
#include "ui_player_info_component.hpp"
#include "ui_gamelog_component.hpp"
#include <string>
#include <memory>

namespace ui_layer {

	void init_components(const Player& player, const std::deque<std::string>& log_buffer) {
		//auto gamelogComponent = std::make_shared<GamelogComponent>(0,0, ascii::WIDTH, 3, log_buffer);
		auto playerInfoComponent = std::make_shared<PlayerInfoComponent>(0,int(ascii::HEIGHT)-10, int(ascii::WIDTH), 10, player);
		//ui::add_component(gamelogComponent);
		ui::add_component(playerInfoComponent);
}

	}


