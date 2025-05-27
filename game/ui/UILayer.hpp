#ifndef UI_LAYER_HPP
#define UI_LAYER_HPP

#include <deque>
#include <string>
#include <memory>
#include "engine/ui/Rect.hpp"
#include "entity/Player.hpp"

namespace game::entity {
    class Player;
}
namespace game::world {
    class GameWorld;
}

namespace game::ui {
    class RenderAreaComponent;
    class UILayer{
        public:
            UILayer(engine::Renderer& renderer, engine::ui::UIManager& UIManager, const game::world::GameWorld& world, game::entity::Player& player) : renderer_(renderer), UIManager_(UIManager), world_(world), player_(player) {}
            void initComponents();
            Rect getRenderAreaComponent();

        private:
            engine::Renderer& renderer_;
            engine::ui::UIManager& UIManager_;
            const game::world::GameWorld& world_;
            game::entity::Player& player_;
            std::shared_ptr<RenderAreaComponent> renderArea_;
    };
} // namespace Game::UI

#endif // UI_LAYER_HPP
