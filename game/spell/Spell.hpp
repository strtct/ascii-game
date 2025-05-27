#pragma once
#include <string>

namespace game::entity {
    class Player;
}
namespace game::world {
    class GameWorld;
}
namespace engine {
    class Renderer;
}
namespace game::spell {
    class Spell {
       public:
           Spell(const std::string& name, int manaCost, int range)
    : name(name), manaCost(manaCost), range(range) {}

            virtual ~Spell() = default;

            std::string getName() const;
            int getManaCost() const;
            int getRange() const;

            virtual void cast(const game::entity::Player& caster, game::world::GameWorld& world, engine::Renderer& renderer) const = 0;        
       protected:
            std::string name;
            int manaCost;
            int range;
 
    };
}
