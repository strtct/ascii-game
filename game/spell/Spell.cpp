#include "Spell.hpp"

using namespace game::spell;


std::string Spell::getName() const { return name; }
int Spell::getManaCost() const { return manaCost; }
int Spell::getRange() const { return range; }
