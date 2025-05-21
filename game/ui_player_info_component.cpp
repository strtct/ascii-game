#include "engine/ascii_renderer.hpp"
#include "engine/ui/rect.hpp"
#include "player.hpp"
#include "ui_player_info_component.hpp"

    PlayerInfoComponent::PlayerInfoComponent(int x_, int y_, int w_, int h_, const Player& player_)
        : x(x_), y(y_), width(w_), height(h_), player(player_) {}

	//x = 0;
    //y = ascii::HEIGHT - UI_PANEL_HEIGHT;
    //width = ascii::WIDTH;
    //height = UI_PANEL_HEIGHT;
    
	int PlayerInfoComponent::getX() const { return x; }
    int PlayerInfoComponent::getY() const { return y; }
    int PlayerInfoComponent::getWidth() const { return width; }
    int PlayerInfoComponent::getHeight() const { return height; }
	
	Rect PlayerInfoComponent::getBounds() const {
        return Rect{x, y, width, height};
    }
	
	void PlayerInfoComponent::draw() const {
		// Dibujar bordes
		// Dibujar borde superior e inferior
		for (int xPos = x; xPos < x + width; ++xPos) {
		    ascii::draw_char(xPos, y, '-');                 // borde superior
    		ascii::draw_char(xPos, y + height - 1, '-');    // borde inferior
		}

		// Dibujar borde izquierdo y derecho
		for (int yPos = y; yPos < y + height; ++yPos) {
    		ascii::draw_char(x, yPos, '|');                  // borde izquierdo
    		ascii::draw_char(x + width - 1, yPos, '|');      // borde derecho
		}

		// Dibujar las esquinas
		ascii::draw_char(x, y, '+');
		ascii::draw_char(x + width - 1, y, '+');
		ascii::draw_char(x, y + height - 1, '+');
		ascii::draw_char(x + width - 1, y + height - 1, '+');
		
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


        //clearArea();
		int line = y + 1;

		ascii::draw_text(col1X + 2, line++, "Pos: x" + std::to_string(player_x) + " y" + std::to_string(player_y) + " z" + std::to_string(player_z)) ;
		ascii::draw_text(col1X + 2, line++, "Dir: x" + std::to_string(facing_x) + " y" +std::to_string(facing_y) + " z" + std::to_string(facing_z) );
		line++;
		ascii::draw_text(col1X + 2, line++, "HP:  " + std::to_string(player.getCurrentHealth()) + "/" + std::to_string(player.getMaxHealth()));
		ascii::draw_text(col1X + 2, line++, "MP:  " + std::to_string(player.getCurrentMana()) + "/" + std::to_string(player.getMaxMana()));
    	ascii::draw_text(col1X + 2, line++, "Lvl: " + std::to_string(player.getLevel()));

		line = y + 1;
    	ascii::draw_text(col2X + 2, line++, "STR: " + std::to_string(player.getStrength()));
    	ascii::draw_text(col2X + 2, line++, "INT: " + std::to_string(player.getIntelligence()));
    	ascii::draw_text(col2X + 2, line++, "AGI: " + std::to_string(player.getAgility()));

		line = y + 1;
    	ascii::draw_text(col3X + 2, line++, "DEX: " + std::to_string(player.getDexterity()));
    	ascii::draw_text(col3X + 2, line++, "VIT: " + std::to_string(player.getVitality()));
		
	}
	void PlayerInfoComponent::resize(int newWidth, int newHeight) {
    	width = newWidth;
    	y = newHeight - height; 
	}

