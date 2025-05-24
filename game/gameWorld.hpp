#pragma once
#include <vector>
#include "position.hpp"
#include "ui_layer.hpp"
class Entity;
class Player;
class GameWorld {
public:
	GameWorld();
    void addEntity(Entity* e);
    void removeEntity(Entity* e);
    Entity* getEntityAt(const Position& pos);
    void updateAll();
	void renderAll(const Player& player) const;
	int getMapHeight() const;
	int getMapWidth() const;
	void generateTerrain();
	static constexpr int MAP_HEIGHT = 1000;
	static constexpr int MAP_WIDTH = 1000;

private:
    std::vector<Entity*> entities;
	std::vector<std::vector<char>> terrainLayer;

};
