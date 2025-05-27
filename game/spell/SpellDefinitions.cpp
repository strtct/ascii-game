#include "SpellDefinitions.hpp"
#include "FireballSpell.hpp"

using namespace game::spell;

void SpellDefinitions::initialize() {
    AllSpells_.push_back(std::make_shared<game::spell::FireballSpell>());
}
