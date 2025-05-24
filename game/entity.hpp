#pragma once
#include "position.hpp"
#include <string>
class GameWorld;
class Entity {
public:
	Entity(const std::string& name, const char renderChar, const Position& position, const Position& facingDirection);
		
	// Getters
	virtual const std::string& getName() const { return name_; }
	virtual char getRenderChar() const { return renderChar_; }
    virtual const Position& getPosition() const { return position_;  }
	virtual const Position& getFacingDirection() const { return facingDirection_; }

	// Setters	
    virtual void setPosition(const Position& position) { position_ = position; }
	virtual void setFacingDirection(const Position& dir) {facingDirection_=dir; }
    //virtual void update(GameWorld&) = 0;
    virtual void render() const = 0;
	// Logic
    virtual void takeDamage(int) = 0;
	virtual void move(int dx, int dy, float dz, const GameWorld& world);
	// Destruct
    virtual ~Entity() = default;
protected:
	const std::string name_;
	Position position_;
	Position facingDirection_;
	const char renderChar_;
};
