#include "Player.hpp"
#include <string>
#include "Character.hpp"
#include "world/Position.hpp"
#include "engine/ui/UIManager.hpp"
#include "spell/Spell.hpp"

using namespace game::entity;

// Constructor
Player::Player(
	const std::string& name, const char renderChar, int level,  
	game::world::Position position, Position facingDirection, int strength, 
	int intelligence, int agility, int dexterity, int vitality, engine::Renderer& renderer, game::world::GameWorld& world, engine::ui::UIManager& UIManager)
    : Character(name, renderChar, position, facingDirection, level, strength, intelligence, agility, dexterity, vitality, calculateMaxHealth(level, vitality), calculateMaxHealth(level, vitality), calculateMaxMana(level, intelligence), calculateMaxMana(level, intelligence), renderer, world), UIManager_(UIManager)
{
}

// Destructor
Player::~Player() {}

// Métodos de cálculo
int Player::calculateMaxHealth(int level, int vitality) const {
    return vitality * 1.5 + level * 5;
}

int Player::calculateMaxMana(int level, int intelligence) const {
    return intelligence * 1.8 + level * 3;
}

// Lógica
bool Player::castSpell(const game::spell::Spell& spell) {
    if (currentMana_ >= spell.getManaCost()) {
        currentMana_ -= spell.getManaCost();
        spell.cast(*this, world_, renderer_);
		return true;
    } else {
		UIManager_.addLog("not enough mana to cast " + spell.getName());
		return false;
    }
}
void Player::render() {
}
//void Player::update() const {
//}
