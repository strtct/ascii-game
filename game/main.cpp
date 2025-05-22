#include "engine/ascii_renderer.hpp"
#include "engine/ui/ui_manager.hpp"

#include <thread>
#include <chrono>
#include <iostream>
#include "engine/input.hpp"
#include "player.hpp"
#include "position.hpp"
#include "gameWorld.hpp"
#include "fireballSpell.h"
#include "ui_layer.hpp"
#include <csignal>
#include <termios.h>
#include <unistd.h>
#include <cstdlib>
int main() {

	GameWorld world;
	// Obtenemos el tamaño del mapa desde GameWorld
    int mapWidth = world.getMapWidth();
    int mapHeight = world.getMapHeight();

    // Calculamos el centro del mapa
    int centerX = mapWidth / 2;
    int centerY = mapHeight / 2;
    float centerZ = 0.0f;
    Position centerPos(centerX, centerY, centerZ);

	Player player ("Stratcat", 1, 10, 22, 10, 14, 14, centerPos);
    FireballSpell fireball; 
	ascii::init();

	world.addEntity(&player);

	ui::init();

	input::init();
    atexit(input::shutdown);

    bool running = true;

	ui_layer::init_components(player, ui::get_log_buffer());

    while (running) {


		ascii::update_terminal_size();
		ascii::clear();		
		ui::resize_all(int(ascii::WIDTH), int(ascii::HEIGHT));

		world.updateAll();
		world.renderAll(player);
		ui::draw_all();
		ascii::render();
        // Procesar entrada
		char key;
    	bool got_key, got_mouse;
		input::MouseEvent me;
		input::update_key_state();
		input::poll_input(key, got_key, me, got_mouse);
		float dx = 0, dy = 0;
		int speed = 1;
	    if (input::is_key_pressed('w')) dy -= speed;
    	if (input::is_key_pressed('s')) dy += speed;
	    if (input::is_key_pressed('a')) dx -= speed;
    	if (input::is_key_pressed('d')) dx += speed;
		
	    player.move(dx, dy,0,world);  
		
        if (got_key) {
    		switch (key) {
	        	case 'q': running = false; break;
               	case ' ': player.castSpell(fireball, world); break;
            	    // … otros “one-shot” …
        	}
    	}
	    if (got_mouse) {
        	ui::on_mouse_click(me.x, me.y);
        }

        // Pequeño retraso para evitar usar 100% CPU
        std::this_thread::sleep_for(std::chrono::milliseconds(33));
    }

    ui::shutdown();
    ascii::shutdown();
    input::shutdown();
    return 0;
}
