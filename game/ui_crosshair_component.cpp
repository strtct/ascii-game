#include "ui_crosshair_component.hpp"
#include "player.hpp"
#include "engine/ascii_renderer.hpp"
#include "gameWorld.hpp"
void CrosshairComponent::draw() const {
	int playerx = player_.getPosition().x;
	int playery = player_.getPosition().y;

	int offsetX = world_.getOffsetX();
	int offsetY = world_.getOffsetY();
	ascii::draw_char(
		playerx + player_.getFacingDirection().x - offsetX, 
		playery + player_.getFacingDirection().y - offsetY, 
		'+', ascii::Color::BLUE
	);
};
