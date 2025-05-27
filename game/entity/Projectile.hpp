#pragma once
#include "world/Position.hpp"
#include "Entity.hpp"

namespace game::world {
    class GameWorld;
}
namespace engine {
    class Renderer;
}
namespace game::entity {
    class Projectile : public Entity {

        public:
            Projectile(const std::string& name, const char renderChar, Position position, Position velocity, int damage, int range, engine::Renderer& renderer, game::world::GameWorld& world);

            void update();
            void render() override;
            void takeDamage(int) override {} // no-op

        private:
            Position velocity_;
            int damage_;
            int remainingRange_;
            int traveled_ = 0;
            //Team team;
    };
}
