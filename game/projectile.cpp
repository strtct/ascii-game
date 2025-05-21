#include "projectile.hpp"
#include "gameWorld.hpp"
#include "engine/ascii_renderer.cpp"
//Projectile::Projectile(Position pos, Position velocity, int damage, int range, Team team)
Projectile::Projectile(Position pos, Position velocity, int damage, int range)
//    : position(pos), velocity(velocity), damage(damage), remainingRange(range), team(team) {}
    : position(pos), velocity(velocity), damage(damage), remainingRange(range) {}

Position Projectile::getPosition() const {
    return position;
}

void Projectile::setPosition(const Position& pos) {
    position = pos;
}

//Team Projectile::getTeam() const {
//    return team;
//}

void Projectile::update(GameWorld& world) {
    if (remainingRange-- <= 0) {
        world.removeEntity(this);
        return;
    }

    Position next = position + velocity;
    Entity* hit = world.getEntityAt(next);

    //if (hit && hit->getTeam() != team) {
    if (hit) {
        hit->takeDamage(damage);
        world.removeEntity(this); // impacta y desaparece
    } else {
        position = next;
    }
}
void Projectile::render() const {
    ascii::draw_char(position.x, position.y, getRenderChar());
}
char Projectile::getRenderChar() const {
    return '*';  // símbolo para el proyectil
}

