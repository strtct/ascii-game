#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "Character.hpp"
#include "world/Position.hpp"
namespace game::spell {
    class Spell;
}
namespace engine {
    class Renderer;
    namespace ui {
        class UIManager;
    }
}
namespace game::entity {
    class Player : public Character {
        public:
            Player(
                    const std::string& name, const char renderChar, int level, 
                    Position position, Position facingDirection, 
                    int strength, int intelligence, int agility, int dexterity, 
                    int vitality, engine::Renderer& renderer, game::world::GameWorld& world, engine::ui::UIManager& UIManager
                  );
            virtual ~Player();
            bool castSpell(const game::spell::Spell& spell) override;
            void render() override;
            //void update() const;
        private:
            // Métodos internos de cálculo
            int calculateMaxHealth(int level, int vitality) const;
            int calculateMaxMana(int level, int intelligence) const;
            engine::ui::UIManager& UIManager_;
    };
}
#endif // PLAYER_H
