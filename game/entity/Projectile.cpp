#include "Projectile.hpp"
#include "world/GameWorld.hpp"
#include "Entity.hpp"

using namespace game::entity;

Projectile::Projectile(const std::string& name, const char renderChar, Position position, Position velocity, int damage, int range, engine::Renderer& renderer, game::world::GameWorld& world)
    : Entity(name, renderChar, position, position, renderer, world), velocity_(velocity), damage_(damage), remainingRange_(range) {}


void Projectile::update() {
    if (remainingRange_-- <= 0) {
        world_.removeEntity(this);
        return;
    }

    Position next = position_ + velocity_;
    Entity* hit = world_.getEntityAt(next);

    if (hit) {
        hit->takeDamage(damage_);
        world_.removeEntity(this);
    } else {
        position_ = next;
    }
}
void Projectile::render() {
    renderer_.drawChar(position_.x, position_.y, getRenderChar());
}

