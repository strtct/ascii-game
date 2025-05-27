#include "engine/Renderer.hpp"
#include "engine/ui/Rect.hpp"
#include "entity/Player.hpp"
#include "PlayerInfoComponent.hpp"
#include "engine/ui/UIManager.hpp"

using namespace game::ui;

void PlayerInfoComponent::draw() const {
	
	// Dibujar borde superior e inferior
	for (int xPos = x_; xPos < x_ + width_; ++xPos) {
		renderer_.drawChar(xPos, y_, '-');
    	renderer_.drawChar(xPos, y_ + height_ - 1, '-');
	}

	// Dibujar borde izquierdo y derecho
	for (int yPos = y_; yPos < y_ + height_; ++yPos) {
    	renderer_.drawChar(x_, yPos, '|');
    	renderer_.drawChar(x_ + width_ - 1, yPos, '|');
	}

	// Dibujar las esquinas
	renderer_.drawChar(x_, y_, '+');
	renderer_.drawChar(x_ + width_ - 1, y_, '+');
	renderer_.drawChar(x_, y_ + height_ - 1, '+');
	renderer_.drawChar(x_ + width_ - 1, y_ + height_ - 1, '+');
		
	int player_x = player_.getPosition().x;
	int player_y = player_.getPosition().y;
	int player_z = player_.getPosition().z;
	int facing_x = player_.getFacingDirection().x;
	int facing_y = player_.getFacingDirection().y;
	int facing_z = player_.getFacingDirection().z;
	int columnWidth = width_ / 3;
	
	// sólo para depuración
	
	// Coordenadas base de cada columna
    int col1X = 1;
	int col2X = columnWidth + 1;
    int col3X = columnWidth * 2 + 1;


	int line = y_ + 1;

	renderer_.drawText(col1X + 2, line++, "Pos: x" + std::to_string(player_x) + " y" + std::to_string(player_y) + " z" + std::to_string(player_z)) ;
	renderer_.drawText(col1X + 2, line++, "Dir: x" + std::to_string(facing_x) + " y" +std::to_string(facing_y) + " z" + std::to_string(facing_z) );
	line++;
	renderer_.drawText(col1X + 2, line++, "HP:  " + std::to_string(player_.getCurrentHealth()) + "/" + std::to_string(player_.getMaxHealth()));
	renderer_.drawText(col1X + 2, line++, "MP:  " + std::to_string(player_.getCurrentMana()) + "/" + std::to_string(player_.getMaxMana()));
    renderer_.drawText(col1X + 2, line++, "Lvl: " + std::to_string(player_.getLevel()));

	line = y_ + 1;
    renderer_.drawText(col2X + 2, line++, "STR: " + std::to_string(player_.getStrength()));
    renderer_.drawText(col2X + 2, line++, "INT: " + std::to_string(player_.getIntelligence()));
    renderer_.drawText(col2X + 2, line++, "AGI: " + std::to_string(player_.getAgility()));

	
	line = y_ + 1;
    renderer_.drawText(col3X + 2, line++, "DEX: " + std::to_string(player_.getDexterity()));
    renderer_.drawText(col3X + 2, line++, "VIT: " + std::to_string(player_.getVitality()));
		
}
	
void PlayerInfoComponent::resize(int newWidth, int newHeight) {
    width_ = newWidth;
    y_ = newHeight - vindex_; 
}

