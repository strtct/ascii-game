#include "engine/ascii_renderer.hpp"
#include "engine/ui/rect.hpp"
#include "player.hpp"
#include "ui_player_info_component.hpp"
#include "engine/ui/ui_manager.hpp"

void PlayerInfoComponent::draw() const {
	
	// Dibujar borde superior e inferior
	for (int xPos = x_; xPos < x_ + width_; ++xPos) {
		ascii::draw_char(xPos, y_, '-');
    	ascii::draw_char(xPos, y_ + height_ - 1, '-');
	}

	// Dibujar borde izquierdo y derecho
	for (int yPos = y_; yPos < y_ + height_; ++yPos) {
    	ascii::draw_char(x_, yPos, '|');
    	ascii::draw_char(x_ + width_ - 1, yPos, '|');
	}

	// Dibujar las esquinas
	ascii::draw_char(x_, y_, '+');
	ascii::draw_char(x_ + width_ - 1, y_, '+');
	ascii::draw_char(x_, y_ + height_ - 1, '+');
	ascii::draw_char(x_ + width_ - 1, y_ + height_ - 1, '+');
		
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

	ascii::draw_text(col1X + 2, line++, "Pos: x" + std::to_string(player_x) + " y" + std::to_string(player_y) + " z" + std::to_string(player_z)) ;
	ascii::draw_text(col1X + 2, line++, "Dir: x" + std::to_string(facing_x) + " y" +std::to_string(facing_y) + " z" + std::to_string(facing_z) );
	line++;
	ascii::draw_text(col1X + 2, line++, "HP:  " + std::to_string(player_.getCurrentHealth()) + "/" + std::to_string(player_.getMaxHealth()));
	ascii::draw_text(col1X + 2, line++, "MP:  " + std::to_string(player_.getCurrentMana()) + "/" + std::to_string(player_.getMaxMana()));
    ascii::draw_text(col1X + 2, line++, "Lvl: " + std::to_string(player_.getLevel()));

	line = y_ + 1;
    ascii::draw_text(col2X + 2, line++, "STR: " + std::to_string(player_.getStrength()));
    ascii::draw_text(col2X + 2, line++, "INT: " + std::to_string(player_.getIntelligence()));
    ascii::draw_text(col2X + 2, line++, "AGI: " + std::to_string(player_.getAgility()));

	
	line = y_ + 1;
    ascii::draw_text(col3X + 2, line++, "DEX: " + std::to_string(player_.getDexterity()));
    ascii::draw_text(col3X + 2, line++, "VIT: " + std::to_string(player_.getVitality()));
		
}
	
void PlayerInfoComponent::resize(int newWidth, int newHeight) {
    width_ = newWidth;
    y_ = newHeight - vindex_; 
}

