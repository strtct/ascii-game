#pragma once
#include <string>

class Player;
class GameWorld;

class Spell {
protected:
    std::string name;
    int manaCost;
    int range;

public:
    Spell(const std::string& name, int manaCost, int range);
    virtual ~Spell() = default;

    std::string getName() const;
    int getManaCost() const;
    int getRange() const;

    virtual void cast(Player& caster, GameWorld& world) const = 0;
};
