#include "engine/ui/ui_component.hpp"
#include "engine/ui/rect.hpp"
#include "engine/ui/ui_manager.hpp"
#include "ui_render_area.hpp"
#include <memory>
class Player;
class GameWorld;
class CrosshairComponent : public ui::UIComponent {
	public:
		CrosshairComponent(int x, int y, int width, int height, int zindex, int vindex, const Player& player, const GameWorld& world) : UIComponent (x, y, width, height, zindex, vindex), player_(player), world_(world) {}
    	UIType getType() const override { return UIType::Blocking; }
    	void draw() const override;
		void resize(int newWidth, int newHeight) override {
		};
private:
	const Player& player_;
	const GameWorld& world_;
};
