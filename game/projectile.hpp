#pragma once
#include "entity.hpp"
#include "position.hpp"

class GameWorld;

class Projectile : public Entity {
public:
    //Projectile(Position pos, Position velocity, int damage, int range, Team team);
    Projectile(const std::string& name, const char renderChar, Position position, Position velocity, int damage, int range);

    void update(GameWorld& world);
	void render() const override;
    void takeDamage(int) override {} // no-op

private:
    Position velocity_;
    int damage_;
    int remainingRange_;
	int traveled_ = 0;
    //Team team;
};
