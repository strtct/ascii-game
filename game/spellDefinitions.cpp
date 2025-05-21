#include "spellDefinitions.hpp"
#include "fireballSpell.h"

std::vector<std::shared_ptr<Spell>> SpellDefinitions::AllSpells;

void SpellDefinitions::initialize() {
    AllSpells.push_back(std::make_shared<FireballSpell>());
}
