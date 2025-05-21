#include "engine/ascii_renderer.hpp"
#include "engine/ui_manager.hpp"

#include <thread>
#include <chrono>
#include <iostream>
#include "engine/input.hpp"
#include "player.hpp"
#include "position.hpp"
#include "gameWorld.hpp"
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
    
	ascii::init();

	world.addEntity(&player);

	ui::init();

	input::init();
    atexit(input::shutdown);

    bool running = true;

    while (running) {

        // Dibujar la UI (log)
        ui::draw_log_panel();

        // Mostrar en pantalla
		world.updateAll();
		world.renderAll(player);

        // Procesar entrada
		char key;
		bool got_key, got_mouse;
		input::MouseEvent me;

		if (input::poll_input(key, got_key, me, got_mouse)) {
    		if (got_key) {
				switch(key) {
					case 'w': player.move(0,-1,0,world);  break;
					case 's': player.move(0,1,0,world);  break;
					case 'a': player.move(-1,0,0,world);  break;
					case 'd': player.move(1,0,0,world);  break;
					case 'q': running = false; break;
					default:
						ui::add_log(std::string("Tecla: ") +key);
						break;
				}
            }
            if (got_mouse) {
			    ui::on_mouse_click(me.x ,me.y);
            }
        }

        // Pequeño retraso para evitar usar 100% CPU
        std::this_thread::sleep_for(std::chrono::milliseconds(33));
    }

    ui::shutdown();
    ascii::shutdown();
    input::shutdown();
    return 0;
}
