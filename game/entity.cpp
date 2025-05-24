#include "entity.hpp"
#include <string>
#include "gameWorld.hpp"

Entity::Entity(const std::string& name, const char renderChar, const Position& position, const Position& facingDirection) : name_(name), renderChar_(renderChar), position_(position), facingDirection_(facingDirection){}

void Entity::move(int dx, int dy, float dz, const GameWorld& world) {
	Position newPos = position_;
	newPos.x += dx;
	newPos.y += dy;
	newPos.z += dz;

	// Comprobar que newPos está dentro del mapa
    if (newPos.x >= 0 && newPos.x < world.getMapWidth() &&
        newPos.y >= 0 && newPos.y < world.getMapHeight()) {
        // Aquí añadir comprobaciones adicionales (colisiones, obstáculos...)
        position_ = newPos;
    } else {
        // efecto si intentó moverse fuera del mapa
    }
}
