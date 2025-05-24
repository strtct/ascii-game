#include "player.hpp"
#include "engine/ascii_renderer.hpp"
#include <string>
#include "character.hpp"
#include "position.hpp"
#include "engine/ui/ui_manager.hpp"
// Constructor
Player::Player(
	const std::string& name, const char renderChar, int level,  
	const Position& position, const Position& facingDirection, int strength, 
	int intelligence, int agility, int dexterity, int vitality)
    : Character(name, renderChar, level, position, facingDirection, strength, intelligence, agility, dexterity, vitality, calculateMaxHealth(level, vitality), calculateMaxHealth(level, vitality), calculateMaxMana(level, intelligence), calculateMaxMana(level, intelligence))
{
}

// Métodos de cálculo
int Player::calculateMaxHealth(int level, int vitality) const {
    return vitality * 1.5 + level * 5;
}

int Player::calculateMaxMana(int level, int intelligence) const {
    return intelligence * 1.8 + level * 3;
}

// Lógica
bool Player::castSpell(const Spell& spell, GameWorld& world) {
    if (currentMana_ >= spell.getManaCost()) {
        currentMana_ -= spell.getManaCost();
        spell.cast(*this, world);
		return true;
    } else {
			ui::add_log("not enough mana to cast " + spell.getName());
			return false;
    }
}
void Player::render() const {
    ascii::draw_char(position_.x, position_.y, '@'); 
}

