#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "entity.hpp"
#include "position.hpp"
class Spell;
class GameWorld;

class Player : public Entity {
public:
	//int x, y, z;
    // Constructor
    Player(const std::string& name, int level, 
           int strength, int intelligence, int agility, 
           int dexterity, int vitality, const Position& position);

    // Métodos getter
    std::string getName() const;
    int getLevel() const;
    int getStrength() const;
    int getIntelligence() const;
    int getAgility() const;
    int getDexterity() const;
    int getVitality() const;
    int getMaxHealth() const;
    int getCurrentHealth() const;
    int getMaxMana() const;
    int getCurrentMana() const;
	Position getFacingDirection() const;
	char getRenderChar() const override { return '@'; }
	void setFacingDirection(const Position& dir);
	Position getPosition() const override { return position; };
	//Team getTeam() const override;
	
	// Métodos Setter	
	void setPosition(const Position& pos) override { position = pos; };
	// Otros
	void castSpell(const Spell& spell, GameWorld& world);
	void update(GameWorld& world) override {}
	void render() const override;
	void move(int dx, int dy, float dz, const GameWorld& world);
	void takeDamage(int amount) override;

	
private:
    std::string name;
    int level;

    // Atributos base
    int strength;
    int intelligence;
    int agility;
    int dexterity;
    int vitality;

    // Vida y maná
    int maxHealth;
    int currentHealth;
    int maxMana;
    int currentMana;

	Position position;
	Position facingDirection = {1, 0};
	// Team team = Team::Player;

    // Métodos internos de cálculo
    int calculateMaxHealth() const;
    int calculateMaxMana() const;
};

#endif // PLAYER_H
