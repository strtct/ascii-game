#include "engine/ui/UIComponent.hpp"
#include "engine/ui/Rect.hpp"
#include "engine/ui/UIManager.hpp"
#include "RenderArea.hpp"
#include <memory>
namespace game::entity {
    class Player;
}
namespace game::world {
    class GameWorld;
}
namespace game::ui {
    class CrosshairComponent : public engine::ui::UIComponent {
        public:
            CrosshairComponent(int x, int y, int width, int height, int zindex, int vindex, engine::Renderer& renderer, const game::entity::Player& player, const game::world::GameWorld& world) : engine::ui::UIComponent (x, y, width, height, zindex, vindex, renderer), player_(player), world_(world) {}
            UIType getType() const override { return UIType::Blocking; }
            void draw() const override;
            void resize(int newWidth, int newHeight) override {};
        private:
            const game::entity::Player& player_;
            const game::world::GameWorld& world_;
    };
}
