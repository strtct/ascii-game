#include "projectile.hpp"
#include "gameWorld.hpp"
#include "engine/ascii_renderer.cpp"

Projectile::Projectile(const std::string& name, const char renderChar, Position position, Position velocity, int damage, int range)
    : Entity(name, renderChar, position, position), velocity_(velocity), damage_(damage), remainingRange_(range) {}


void Projectile::update(GameWorld& world) {
    if (remainingRange_-- <= 0) {
        world.removeEntity(this);
        return;
    }

    Position next = position_ + velocity_;
    Entity* hit = world.getEntityAt(next);

    if (hit) {
        hit->takeDamage(damage_);
        world.removeEntity(this);
    } else {
        position_ = next;
    }
}
void Projectile::render() const {
    ascii::draw_char(position_.x, position_.y, getRenderChar());
}

