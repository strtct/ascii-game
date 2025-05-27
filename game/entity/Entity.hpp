#pragma once
#include "world/Position.hpp"
#include <string>

namespace game::world {
    class GameWorld;
    struct Position;
}
namespace engine {
    class Renderer;
}
using game::world::Position;
namespace game::entity {
    class Entity {
        public:
            Entity(const std::string& name, const char renderChar, Position position, Position facingDirection, engine::Renderer& renderer, game::world::GameWorld& world);

            // Getters
            virtual const std::string& getName() const { return name_; }
            virtual char getRenderChar() const { return renderChar_; }
            virtual const Position& getPosition() const { return position_;  }
            virtual const Position& getFacingDirection() const { return facingDirection_; }

            // Setters	
            virtual void setPosition(Position& position) { position_ = position; }
            virtual void setFacingDirection(Position& dir) {facingDirection_=dir; }
            //virtual void update(GameWorld&);
            virtual void render() = 0;
            //virtual void update() const;
            // Logic
            virtual void takeDamage(int) = 0;
            virtual void move(int dx, int dy, float dz);
            // Destruct
            virtual ~Entity() = default;
        protected:
            const std::string name_;
            const char renderChar_;
            Position position_;
            Position facingDirection_;
            engine::Renderer& renderer_;
            game::world::GameWorld& world_;
    };
}
