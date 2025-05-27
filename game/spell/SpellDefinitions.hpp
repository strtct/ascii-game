#pragma once
#include <memory>
#include <vector>
#include "Spell.hpp"

namespace game::spell {
    class SpellDefinitions {
        public:
            SpellDefinitions() {}

            ~SpellDefinitions() = default;

            void initialize();

        private:
            std::vector<std::shared_ptr<game::spell::Spell>> AllSpells_;
    };
}
