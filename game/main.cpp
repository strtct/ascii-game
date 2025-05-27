#include "engine/Renderer.hpp"
#include "engine/ui/UIManager.hpp"

#include <thread>
#include <chrono>
#include <iostream>
#include "engine/InputManager.hpp"
#include "entity/Player.hpp"
#include "world/Position.hpp"
#include "world/GameWorld.hpp"
#include "spell/FireballSpell.hpp"
#include "ui/UILayer.hpp"
#include <csignal>
#include <termios.h>
#include <unistd.h>
#include <cstdlib>
#include "/usr/include/linux/input-event-codes.h"
#include <string>
#include "world/Direction.hpp"
#include "math/direction_from_delta.hpp"

class RenderAreaComponent;

//using namespace game;

int main() {
    engine::Renderer renderer;	
	renderer.init();
	
    engine::ui::UIManager UIManager(renderer);
    
	UIManager.init();


    game::world::GameWorld world(renderer, UIManager);
    
	// Obtenemos el tamaño del mapa desde GameWorld
    int mapWidth = world.getMapWidth();
    int mapHeight = world.getMapHeight();

    // Calculamos el centro del mapa
    int centerX = mapWidth / 2;
    int centerY = mapHeight / 2;
    float centerZ = 0.0f;
    game::world::Position centerPos(centerX, centerY, centerZ);
    
    game::entity::Player player ("Stratcat", '@', 1, centerPos, {1,0}, 10, 22, 10, 14, 14, renderer, world, UIManager);
    
    game::ui::UILayer UILayer(renderer, UIManager, world, player);
    game::spell::FireballSpell fireball;
	world.addEntity(&player);
    
	UIManager.init();
    
	engine::InputManager inputManager;
    
    try {
        inputManager.init("/dev/input/event3", "/dev/input/event16");
    } catch (const std::exception& e) {
        std::cerr << "Error en input::init(): " << e.what() << std::endl;
		return 0;
    }
    atexit(inputManager.shutdownStatic);
    
    bool running = true;


    UILayer.initComponents();

    while (running) {

       
		renderer.updateTerminalSize();
		renderer.clear();
        
		UIManager.resizeAll(renderer.getCols(), renderer.getRows());
        
		world.updateAll();
		world.renderAll(player, UILayer.getRenderAreaComponent());
        
		UIManager.drawAll();
		renderer.render();
        // Procesar entrada
		try {
		    inputManager.pollKeyboard();
		} catch (const std::exception& e) {
		    std::cerr << "Error en input::poll(): " << e.what() << std::endl;
		    running = false; 
		}
		try {
		    inputManager.pollMouse();
		} catch (const std::exception& e) {
			std::string error_msg = e.what();
			UIManager.addLog( "Error en input::poll_mouse(): " + error_msg );
		}
        engine::MouseState mouseState = inputManager.getMouseState();
		int mx = mouseState.x;
        int my = mouseState.y;
		if (mouseState.leftPressed) {
            UIManager.addLog("Left button is pressed");
        }

        if (mouseState.scrollVertical != 0) {
            if (mouseState.scrollVertical > 0)
                UIManager.addLog("Scroll UP");
            else
                UIManager.addLog("Scroll DOWN");

			inputManager.resetMouseScroll();
        }
        game::world::Position player_position = player.getPosition();
		Position direction = math::getDirectionFromDelta(mx,my, player_position.x, player_position.y, world.getOffsetX(), world.getOffsetY());
	
		player.setFacingDirection(direction);
		
        float dx = 0, dy = 0;
		int speed = 1;
	    if (inputManager.isKeyPressed(KEY_W)) dy -= speed;
    	if (inputManager.isKeyPressed(KEY_S)) dy += speed;
	    if (inputManager.isKeyPressed(KEY_A)) dx -= speed;
    	if (inputManager.isKeyPressed(KEY_D)) dx += speed;
		if (inputManager.isKeyPressedOnce(KEY_SPACE)) player.castSpell(fireball);
		if (inputManager.isKeyPressedOnce(KEY_ESC)) running = false;
		
        //player.update();	
	    
        player.move(dx, dy,0);  
		

        // Pequeño retraso para evitar usar 100% CPU
        std::this_thread::sleep_for(std::chrono::milliseconds(33));
    }
    
    UIManager.shutdownStatic();
   
    renderer.shutdownStatic();
    //input::shutdown();
    return 0;
}
