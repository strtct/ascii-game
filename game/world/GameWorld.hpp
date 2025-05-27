#pragma once
#include <vector>
#include "Position.hpp"
#include "ui/UILayer.hpp"
#include "engine/Renderer.hpp"
#include "engine/ui/UIManager.hpp"

namespace game::entity {
    class Entity;
    class Player;
}
namespace engine {
    class Renderer;
}
namespace engine::ui {
    class UIManager;
    struct Rect;
}
namespace game::ui {
    class RenderAreaComponent;
}
namespace game::world {
    class GameWorld {
        public:
            GameWorld(engine::Renderer& renderer, engine::ui::UIManager& UIManager);
            int getOffsetX() const { return current_offset_x_; }
            int getOffsetY() const { return current_offset_y_; }
            void addEntity(game::entity::Entity* e);
            void removeEntity(game::entity::Entity* e);
            game::entity::Entity* getEntityAt(const Position& pos);
            void updateAll();
            void renderAll(const game::entity::Player& player, const Rect render_area);
            int getMapHeight() const;
            int getMapWidth() const;
            void generateTerrain();
            static constexpr int MAP_HEIGHT = 1000;
            static constexpr int MAP_WIDTH = 1000;

        private:
            engine::Renderer& renderer_;
            engine::ui::UIManager& UIManager_;
            int current_offset_x_;
            int current_offset_y_;
            std::vector<game::entity::Entity*> entities;
            std::vector<std::vector<char>> terrainLayer;
            void setOffsetX(int offset) { current_offset_x_ = offset; }
            void setOffsetY(int offset) { current_offset_y_ = offset; }
    };
}
