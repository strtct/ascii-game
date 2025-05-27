#include "CrosshairComponent.hpp"
#include "entity/Player.hpp"
#include "engine/Renderer.hpp"
#include "world/GameWorld.hpp"

using namespace game::ui;

void CrosshairComponent::draw() const {
	int playerx = player_.getPosition().x;
	int playery = player_.getPosition().y;

	int offsetX = world_.getOffsetX();
	int offsetY = world_.getOffsetY();
	renderer_.drawChar(
		playerx + player_.getFacingDirection().x - offsetX, 
		playery + player_.getFacingDirection().y - offsetY, 
		'+', engine::Color::BLUE
	);
};
