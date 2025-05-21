#include "ui_layer.hpp"
#include "player.hpp"
#include "engine/ascii_renderer.hpp"
#include "engine/ui_manager.hpp"
#include <string>


namespace ui_layer {

void draw_player_info(const Player& player) {
    int panelX = 0;
    int panelY = ascii::HEIGHT - UI_PANEL_HEIGHT;
    int width = ascii::WIDTH;
    int height = UI_PANEL_HEIGHT;
	int player_x = player.getPosition().x;
	int player_y = player.getPosition().y;
	int player_z = player.getPosition().z;
	int facing_x = player.getFacingDirection().x;
	int facing_y = player.getFacingDirection().y;
	int facing_z = player.getFacingDirection().z;
	int columnWidth = width / 3;

    // Coordenadas base de cada columna
    int col1X = 1;
    int col2X = columnWidth + 1;
    int col3X = columnWidth * 2 + 1;

    int line = panelY + 1;

    ui::draw_panel(panelX, panelY, width, height, "Player Info");

    ascii::draw_text(col1X + 2, line++, "Pos: x" + std::to_string(player_x) + " y" + std::to_string(player_y) + " z" + std::to_string(player_z)) ;
    ascii::draw_text(col1X + 2, line++, "Dir: x" + std::to_string(facing_x) + " y" +std::to_string(facing_y) + " z" + std::to_string(facing_z) );
	line++;
    ascii::draw_text(col1X + 2, line++, "HP:  " + std::to_string(player.getCurrentHealth()) + "/" + std::to_string(player.getMaxHealth()));
    ascii::draw_text(col1X + 2, line++, "MP:  " + std::to_string(player.getCurrentMana()) + "/" + std::to_string(player.getMaxMana()));
    ascii::draw_text(col1X + 2, line++, "Lvl: " + std::to_string(player.getLevel()));

	line = panelY + 1;
    ascii::draw_text(col2X + 2, line++, "STR: " + std::to_string(player.getStrength()));
    ascii::draw_text(col2X + 2, line++, "INT: " + std::to_string(player.getIntelligence()));
    ascii::draw_text(col2X + 2, line++, "AGI: " + std::to_string(player.getAgility()));

	line = panelY + 1;
    ascii::draw_text(col3X + 2, line++, "DEX: " + std::to_string(player.getDexterity()));
    ascii::draw_text(col3X + 2, line++, "VIT: " + std::to_string(player.getVitality()));

}

}
