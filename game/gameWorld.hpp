#pragma once
#include <vector>
#include "position.hpp"
#include "ui_layer.hpp"
class Entity;
class Player;
class GameWorld {
public:
	GameWorld();
	int getOffsetX() const { return current_offset_x_; }
	int getOffsetY() const { return current_offset_y_; }
    void addEntity(Entity* e);
    void removeEntity(Entity* e);
    Entity* getEntityAt(const Position& pos);
    void updateAll();
	void renderAll(const Player& player);
	int getMapHeight() const;
	int getMapWidth() const;
	void generateTerrain();
	static constexpr int MAP_HEIGHT = 1000;
	static constexpr int MAP_WIDTH = 1000;

private:
	int current_offset_x_;
	int current_offset_y_;
    std::vector<Entity*> entities;
	std::vector<std::vector<char>> terrainLayer;
	void setOffsetX(int offset) { current_offset_x_ = offset; }
	void setOffsetY(int offset) { current_offset_y_ = offset; }
};
