#include "gameWorld.hpp"
#include "engine/ascii_renderer.hpp"
#include <algorithm>
#include "player.hpp"
#include "projectile.hpp"
#include "ui_layer.hpp"
GameWorld::GameWorld() {
	generateTerrain();
}

void GameWorld::addEntity(Entity* e) {
    entities.push_back(e);
}

void GameWorld::removeEntity(Entity* e) {
    entities.erase(std::remove(entities.begin(), entities.end(), e), entities.end());
}

Entity* GameWorld::getEntityAt(const Position& pos) {
    for (Entity* e : entities) {
        if (e->getPosition() == pos)
            return e;
    }
    return nullptr;
}

void GameWorld::updateAll() {
    // Copia defensiva en caso de que se eliminen entidades durante el update
    auto snapshot = entities;
    for (Entity* e : snapshot) {
        if (auto* projectile = dynamic_cast<Projectile*>(e)) {
            projectile->update(*this);
        }
        // añadir aquí otras actualizaciones (enemigos, jugadores, etc)
    }
}

int GameWorld::getMapWidth() const { return MAP_WIDTH; }
int GameWorld::getMapHeight() const { return MAP_HEIGHT; }

void GameWorld::renderAll(const Player& player) const {
	const int VIEW_WIDTH = ascii::WIDTH;
	const int VIEW_HEIGHT = ascii::HEIGHT - ui_layer::UI_PANEL_HEIGHT;

	Position playerPos = player.getPosition();
	// Calcular el offset para centrar la cámara en el jugador
    int offsetX = playerPos.x - VIEW_WIDTH / 2;
    int offsetY = playerPos.y - VIEW_HEIGHT / 2;

    // Clamp para que no se salga del mapa
    if (offsetX < 0) offsetX = 0;
    if (offsetY < 0) offsetY = 0;
    if (offsetX > getMapWidth() - VIEW_WIDTH) offsetX = getMapWidth() - VIEW_WIDTH;
    if (offsetY > getMapHeight() - VIEW_HEIGHT) offsetY = getMapHeight() - VIEW_HEIGHT;

	// Dibujar suelo
	for (int y = 0; y < VIEW_HEIGHT; ++y) {
        for (int x = 0; x < VIEW_WIDTH; ++x) {
            int mapX = offsetX + x;
            int mapY = offsetY + y;

            // Solo dibujamos si está dentro del mapa
            if (mapX >= 0 && mapX < getMapWidth() &&
                mapY >= 0 && mapY < getMapHeight()) {
				char terrainChar = terrainLayer[mapY][mapX];
                ascii::draw_char(x, y, terrainChar);  // Suelo base
            } else {
                ascii::draw_char(x, y, '.');  // Fuera de mapa
            }
        }
    }
	// Dibujar entidades
    for (Entity* e : entities) {
        Position pos = e->getPosition();
        int screenX = pos.x - offsetX;
        int screenY = pos.y - offsetY;

        if (screenX >= 0 && screenX < VIEW_WIDTH &&
            screenY >= 0 && screenY < VIEW_HEIGHT) {
            ascii::draw_char(screenX, screenY, e->getRenderChar());
        }
    }

}

	void GameWorld::generateTerrain() {
    terrainLayer.resize(MAP_HEIGHT, std::vector<char>(MAP_WIDTH, ' '));
    for (int y = 0; y < MAP_HEIGHT; ++y) {
        for (int x = 0; x < MAP_WIDTH; ++x) {
            	int r = rand() % 100;
        	    if (r < 5) terrainLayer[y][x] = ',';   // 5%
    	        else if (r < 2) terrainLayer[y][x] = '\''; // 5%
	            else if (r < 4) terrainLayer[y][x] = '`';  // 5%
	            else if (r < 6) terrainLayer[y][x] = '~';  // 5%
            	else terrainLayer[y][x] = ' '; // resto
        	}
    	}
	}

