#include "damageSpell.hpp"
#include "player.hpp"
#include <iostream>

DamageSpell::DamageSpell(const std::string& name, int manaCost, int range, int damage)
    : Spell(name, manaCost, range), damage(damage) {}

int DamageSpell::getDamage() const { return damage; }

void DamageSpell::cast(Player& caster, GameWorld& /*world*/) const {
    std::cout << caster.getName() << " casts " << name
              << " and deals " << damage << " damage (generic spell)!\n";
}
