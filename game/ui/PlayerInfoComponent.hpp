#ifndef PLAYER_INFO_COMPONENT_HPP
#define PLAYER_INFO_COMPONENT_HPP

#include "engine/ui/UIComponent.hpp"
#include "entity/Player.hpp"
#include "engine/ui/Rect.hpp"
#include "engine/ui/ui_type.hpp"
namespace game::entity {
    class Player;
}
namespace engine {
    class Renderer;
}
namespace game::ui {
	class PlayerInfoComponent : public engine::ui::UIComponent {
	public:
	    PlayerInfoComponent(int x, int y, int width, int height, int zindex, int vindex, engine::Renderer& renderer, const game::entity::Player& player) : engine::ui::UIComponent(x, y, width, height, zindex, vindex, renderer), player_(player){}

    	void draw() const override;
		void resize(int newWidth, int newHeight) override;
    	UIType getType() const override { return UIType::Blocking; }

	private:
    	const game::entity::Player& player_;
	};
}

#endif // PLAYER_INFO_COMPONENT_HPP
