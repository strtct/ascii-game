#include "DamageSpell.hpp"
#include "entity/Player.hpp"
#include <iostream>

using namespace game::spell;

DamageSpell::~DamageSpell() {}

int DamageSpell::getDamage() const { return damage; }

void DamageSpell::cast(const Player& caster, GameWorld& world, engine::Renderer& renderer) const {
    std::cerr << caster.getName() << " casts " << name
              << " and deals " << damage << " damage (generic spell)!\n";
}
