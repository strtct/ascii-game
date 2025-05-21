#pragma once
#include "entity.hpp"
#include "position.hpp"

class GameWorld;

class Projectile : public Entity {
public:
    //Projectile(Position pos, Position velocity, int damage, int range, Team team);
    Projectile(Position pos, Position velocity, int damage, int range);

    void update(GameWorld& world);
	void render() const override;
    char getRenderChar() const override; 
    // Overrides de Entity
    Position getPosition() const override;
    void setPosition(const Position&) override;
    //Team getTeam() const override;
    void takeDamage(int) override {} // no-op

private:
    Position position;
    Position velocity;
    int damage;
    int remainingRange;
    //Team team;
};
