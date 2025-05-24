#include "ui_crosshair_component.hpp"
#include "player.hpp"
#include "engine/ascii_renderer.hpp"
void CrosshairComponent::draw() const {
	ui::add_log("Dibujo el crossairComponent!");
	int playerx = player_.getPosition().x;
	int playery = player_.getPosition().y;

	int offsetX = playerx - renderArea_->getWidth() / 2;
	int offsetY = playery - renderArea_->getHeight() / 2;
	ascii::draw_char(
		playerx + player_.getFacingDirection().x - offsetX, 
		playery + player_.getFacingDirection().y - offsetY, 
		'+'
	);
};
