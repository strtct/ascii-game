#pragma once

#include "spell.h"

class DamageSpell : public Spell {
public:
    DamageSpell(const std::string& name, int manaCost, int range, int damage);

    int getDamage() const;

    void cast(Player& caster, GameWorld& world) const override;

protected:
    int damage;
};
