#pragma once
#include "position.hpp"
//#include "gameWorld.hpp"
//enum class Team {
//    Neutral,
//    Player,
//    Enemy
//};
class GameWorld;
class Entity {
public:
    virtual void update(GameWorld&) = 0;
    virtual void render() const = 0;
    virtual Position getPosition() const = 0;
	virtual char getRenderChar() const = 0;
    virtual void setPosition(const Position&) = 0;
    //virtual int getTeam() const = 0;
    virtual void takeDamage(int) = 0;
    virtual ~Entity() = default;
};
