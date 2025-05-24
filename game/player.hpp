#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "character.hpp"
#include "position.hpp"
#include "spell.hpp"

class GameWorld;

class Player : public Character {
public:
    Player(
		const std::string& name, const char renderChar, int level, 
        const Position& position, const Position& facingDirection, 
		int strength, int intelligence, int agility, int dexterity, 
		int vitality
	);
	
    bool castSpell(const Spell& spell, GameWorld& world) override;
	void render() const override;
private:
    // Métodos internos de cálculo
    int calculateMaxHealth(int level, int vitality) const;
    int calculateMaxMana(int level, int intelligence) const;
};

#endif // PLAYER_H
