#pragma once

#include "Spell.hpp"

using game::entity::Player;
using game::world::GameWorld;
namespace engine {
    class Renderer;
}
namespace game::spell {
    class DamageSpell : public Spell {
        public:
            DamageSpell(const std::string& name, int manaCost, int range, int damage)
    : Spell(name, manaCost, range), damage(damage) {}
            
            virtual ~DamageSpell();

            int getDamage() const;

            void cast(const Player& player, GameWorld& world, engine::Renderer& renderer) const override;

        protected:
            int damage;
    };
}
