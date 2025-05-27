#include "UILayer.hpp"
#include "entity/Player.hpp"
#include "engine/Renderer.hpp"
#include "engine/ui/UIManager.hpp"
#include "PlayerInfoComponent.hpp"
#include "LogComponent.hpp"
#include <string>
#include <memory>
#include "RenderArea.hpp"
#include "CrosshairComponent.hpp"
#include <iostream>
using namespace game::ui;

void UILayer::initComponents() {
	int cols = renderer_.getCols();
	int rows = renderer_.getRows();

	renderArea_ = std::make_shared<RenderAreaComponent>(
		0, 0, int(cols), int(rows) - 13, 0,
		int(rows), renderer_
	);

	auto playerInfoComponent = std::make_shared<PlayerInfoComponent>(
		0,int(rows)-8, int(cols), 8, 0, 8, renderer_, player_
	);
		
	auto logComponent = std::make_shared<LogComponent>(
		0,int(rows)-13, int(cols), 5, 0, 13, renderer_, UIManager_.getLogBuffer()
	);
	
	auto crosshair = std::make_shared<CrosshairComponent>(
		player_.getPosition().x + player_.getFacingDirection().x,
		player_.getPosition().y + player_.getFacingDirection().y,
		1, 1, 4, 0, renderer_, player_, world_
	);
	UIManager_.addComponent(renderArea_);
	UIManager_.addComponent(logComponent);
	UIManager_.addComponent(playerInfoComponent);
	UIManager_.addComponent(crosshair);
}

	Rect UILayer::getRenderAreaComponent() {
    	return renderArea_->getBounds();
	}


