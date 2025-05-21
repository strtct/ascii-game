#include "spell.h"

Spell::Spell(const std::string& name, int manaCost, int range)
    : name(name), manaCost(manaCost), range(range) {}

std::string Spell::getName() const { return name; }
int Spell::getManaCost() const { return manaCost; }
int Spell::getRange() const { return range; }
