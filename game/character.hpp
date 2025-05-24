#pragma once
#include "entity.hpp"
#include "position.hpp"
#include <string>
class Spell;
class GameWorld;

class Character : public Entity {
public:
    Character(
		const std::string& name, const char renderChar, int level, 
		const Position& position, const Position& facingDirection, int strength, 
		int intelligence, int agility, int dexterity, int vitality, 
		int currentHealth, int maxHealth, int currentMana, int maxMana
	);

    // Getters de atributos
	int getLevel() const;
    int getStrength() const;
    int getIntelligence() const;
    int getAgility() const;
    int getDexterity() const;
    int getVitality() const;
	int getCurrentHealth() const;
	int getMaxHealth() const;
    int getCurrentMana() const;
    int getMaxMana() const;

	// Setters
	void setStrength(int);
	void setIntelligence(int);
	void setAgility(int);
	void setDexterity(int);
	void setVitality(int);
	void setCurrentHealth(int);
	void setMaxHealth(int);
	void setCurrentMana(int);
	void setMaxMana(int);

    void takeDamage(int amount);
   	virtual bool castSpell(const Spell& spell, GameWorld& world) = 0;

protected:
	int level_;
    int strength_;
    int intelligence_;
    int agility_;
    int dexterity_;
    int vitality_;
    int currentHealth_;
	int maxHealth_;
	int currentMana_;
    int maxMana_;
};
