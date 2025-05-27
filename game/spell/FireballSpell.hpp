#pragma once
#include "DamageSpell.hpp"

using game::entity::Player;
using game::world::GameWorld;
namespace engine {
    class Renderer;
}

namespace game::spell {
    class FireballSpell : public DamageSpell {
        public:
            FireballSpell()
            : DamageSpell("Fireball", 5, 10, 20) {}

            void cast(const Player& caster, GameWorld& world, engine::Renderer& renderer) const override;
    };
}
