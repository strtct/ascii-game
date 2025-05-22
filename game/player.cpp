#include "player.hpp"
#include "engine/ascii_renderer.hpp"
#include "spell.h"
#include "gameWorld.hpp"
#include <iostream>
#include "engine/ui/ui_manager.hpp"
#include <fstream>
// Constructor
Player::Player(const std::string& name, int level, 
               int strength, int intelligence, int agility, 
               int dexterity, int vitality, const Position& pos)
    : name(name), level(level),
      strength(strength), intelligence(intelligence),
      agility(agility), dexterity(dexterity), vitality(vitality),
      position(pos)
{
    maxHealth = calculateMaxHealth();
    currentHealth = maxHealth;

    maxMana = calculateMaxMana();
    currentMana = maxMana;
}

// Getters
std::string Player::getName() const { return name; }
int Player::getLevel() const { return level; }

int Player::getStrength() const { return strength; }
int Player::getIntelligence() const { return intelligence; }
int Player::getAgility() const { return agility; }
int Player::getDexterity() const { return dexterity; }
int Player::getVitality() const { return vitality; }

int Player::getMaxHealth() const { return maxHealth; }
int Player::getCurrentHealth() const { return currentHealth; }
int Player::getMaxMana() const { return maxMana; }
int Player::getCurrentMana() const { return currentMana; }

// Métodos de cálculo
int Player::calculateMaxHealth() const {
    return vitality * 1.5 + level * 5;
}

int Player::calculateMaxMana() const {
    return intelligence * 1.8 + level * 3;
}

// Lógica
void Player::move(int dx, int dy, float dz, const GameWorld& world) {
	Position newPos = position;
	newPos.x += dx;
	newPos.y += dy;
	newPos.z += dz;

	// Comprobar que newPos está dentro del mapa
    if (newPos.x >= 0 && newPos.x < world.getMapWidth() &&
        newPos.y >= 0 && newPos.y < world.getMapHeight()) {
        // Aquí añadir comprobaciones adicionales (colisiones, obstáculos...)
        position = newPos;
    } else {
        // efecto si intentó moverse fuera del mapa
    }

}
void Player::castSpell(const Spell& spell, GameWorld& world) {
    if (currentMana >= spell.getManaCost()) {
        currentMana -= spell.getManaCost();
        spell.cast(*this, world);
    } else {
			ui::add_log("not enough mana to cast " + spell.getName());
    }
}

void Player::render() const {
    ascii::draw_char(position.x, position.y, '@'); 
}



//Team Player::getTeam() const {
//    return team;
//}

void Player::takeDamage(int amount) {
    currentHealth -= amount;
    if (currentHealth < 0) currentHealth = 0;
}

Position Player::getFacingDirection() const {
    return facingDirection;
}

void Player::setFacingDirection(const Position& dir) {
    facingDirection = dir;
}
