#include "character.hpp"
#include <algorithm>
#include "spell.hpp"
#include "gameWorld.hpp"
#include "entity.hpp"

Character::Character(
	const std::string& name, const char renderChar, int level, 
	const Position& position, 
	const Position& facingDirection, int strength, int intelligence, 
	int agility, int dexterity, int vitality, int currentHealth, int maxHealth, int currentMana, int maxMana)
    : Entity(
		name, renderChar, position, facingDirection
	), 
		level_(level),
      	strength_(strength), dexterity_(dexterity), agility_(agility),
      	vitality_(vitality), intelligence_(intelligence),
      	currentHealth_(maxHealth), maxHealth_(maxHealth), 
		currentMana_(maxMana), maxMana_(maxMana) {}


// Getters
int Character::getLevel() const			 { return level_;}
int Character::getStrength() const       { return strength_; }
int Character::getDexterity() const      { return dexterity_; }
int Character::getAgility() const        { return agility_; }
int Character::getVitality() const       { return vitality_; }
int Character::getIntelligence() const   { return intelligence_; }
int Character::getCurrentHealth() const  { return currentHealth_; }
int Character::getMaxHealth() const      { return maxHealth_; }
int Character::getCurrentMana() const    { return currentMana_; }
int Character::getMaxMana() const        { return maxMana_; }

// Setters
void Character::setStrength(int val)       { strength_ = std::max(0, val); }
void Character::setDexterity(int val)      { dexterity_ = std::max(0, val); }
void Character::setAgility(int val)        { agility_ = std::max(0, val); }
void Character::setVitality(int val)       { vitality_ = std::max(0, val); }
void Character::setIntelligence(int val)   { intelligence_ = std::max(0, val); }

void Character::setCurrentHealth(int val)  { currentHealth_ = std::clamp(val, 0, maxHealth_); }
void Character::setMaxHealth(int val) {
    maxHealth_ = std::max(1, val);
    currentHealth_ = std::min(currentHealth_, maxHealth_);
}

void Character::setCurrentMana(int val)    { currentMana_ = std::clamp(val, 0, maxMana_); }
void Character::setMaxMana(int val) {
    maxMana_ = std::max(0, val);
    currentMana_ = std::min(currentMana_, maxMana_);
}


// Otros métodos útiles
void Character::takeDamage(int dmg) {
    currentHealth_ = std::max(0, currentHealth_ - dmg);
}


