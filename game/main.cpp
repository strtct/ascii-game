#include "engine/ascii_renderer.hpp"
#include "engine/ui/ui_manager.hpp"

#include <thread>
#include <chrono>
#include <iostream>
#include "engine/input.hpp"
#include "player.hpp"
#include "position.hpp"
#include "gameWorld.hpp"
#include "fireballSpell.hpp"
#include "ui_layer.hpp"
#include <csignal>
#include <termios.h>
#include <unistd.h>
#include <cstdlib>
#include "/usr/include/linux/input-event-codes.h"
#include <string>
#include "direction.hpp"
#include "math/direction_from_delta.hpp"

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

	Player player ("Stratcat", '@', 1, centerPos, {1,0}, 10, 22, 10, 14, 14);
    FireballSpell fireball; 
	ascii::init();

	world.addEntity(&player);

	ui::init();
    try {
        input::init("/dev/input/event3", "/dev/input/event8");
    } catch (const std::exception& e) {
        std::cerr << "Error en input::init(): " << e.what() << std::endl;
		return 0;
    }
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
		//input::MouseEvent me;
		//input::update_key_state();
		try {
		    input::poll_keyboard();
		} catch (const std::exception& e) {
		    std::cerr << "Error en input::poll(): " << e.what() << std::endl;
		    running = false; 
		}
		try {
		    input::poll_mouse();
		} catch (const std::exception& e) {
			std::string error_msg = e.what();
			ui::add_log( "Error en input::poll_mouse(): " + error_msg );
		}
		int mx = input::g_mouse.x;
        int my = input::g_mouse.y;
		if (input::g_mouse.leftPressed) {
            ui::add_log("Left button is pressed");
        }

        if (input::g_mouse.scrollVertical != 0) {
            if (input::g_mouse.scrollVertical > 0)
                ui::add_log("Scroll UP");
            else
                ui::add_log("Scroll DOWN");

			input::reset_mouse_scroll();
        }
		Position player_position = player.getPosition();
		Position direction = math::getDirectionFromDelta(mx, my, player_position.x, player_position.y);
		player.setFacingDirection(direction);
		//input::poll();
		float dx = 0, dy = 0;
		int speed = 1;
	    if (input::isKeyPressed(KEY_W)) dy -= speed;
    	if (input::isKeyPressed(KEY_S)) dy += speed;
	    if (input::isKeyPressed(KEY_A)) dx -= speed;
    	if (input::isKeyPressed(KEY_D)) dx += speed;
		if (input::isKeyPressedOnce(KEY_SPACE)) player.castSpell(fireball, world);
		if (input::isKeyPressedOnce(KEY_ESC)) running = false;
		
	    player.move(dx, dy,0,world);  
		
        // Pequeño retraso para evitar usar 100% CPU
        std::this_thread::sleep_for(std::chrono::milliseconds(33));
    }

    ui::shutdown();
    ascii::shutdown();
    //input::shutdown();
    return 0;
}
