#pragma once
#include "damageSpell.hpp"

class FireballSpell : public DamageSpell {
public:
    FireballSpell();

    void cast(Player& caster, GameWorld& world) const override;
};
