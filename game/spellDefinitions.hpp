#pragma once
#include <memory>
#include <vector>

class Spell;

namespace SpellDefinitions {
    extern std::vector<std::shared_ptr<Spell>> AllSpells;

    void initialize();
}
