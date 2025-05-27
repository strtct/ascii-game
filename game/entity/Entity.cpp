#include "Entity.hpp"
#include <string>
#include "world/GameWorld.hpp"

using namespace game::entity;

Entity::Entity(const std::string& name, const char renderChar, Position position, Position facingDirection, engine::Renderer& renderer, game::world::GameWorld& world) : name_(name), renderChar_(renderChar), position_(position), facingDirection_(facingDirection), renderer_(renderer), world_(world){}


void Entity::move(int dx, int dy, float dz) {
	Position newPos = position_;
	newPos.x += dx;
	newPos.y += dy;
	newPos.z += dz;

	// Comprobar que newPos está dentro del mapa
    if (newPos.x >= 0 && newPos.x < world_.getMapWidth() &&
        newPos.y >= 0 && newPos.y < world_.getMapHeight()) {
        // Aquí añadir comprobaciones adicionales (colisiones, obstáculos...)
        position_ = newPos;
    } else {
        // efecto si intentó moverse fuera del mapa
    }
}
