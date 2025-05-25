#ifndef PLAYER_INFO_COMPONENT_HPP
#define PLAYER_INFO_COMPONENT_HPP

#include "engine/ui/ui_component.hpp"
#include "player.hpp"
#include "engine/ui/rect.hpp"
#include "engine/ui/ui_type.hpp"
using ui::UIComponent;

class PlayerInfoComponent : public UIComponent {
public:
    PlayerInfoComponent(int x, int y, int width, int height, int zindex, int vindex, const Player& player) : UIComponent(x, y, width, height, zindex, vindex), player_(player){}

    void draw() const override;
	void resize(int newWidth, int newHeight) override;
    UIType getType() const override { return UIType::Blocking; }

private:
    const Player& player_;
};


#endif // PLAYER_INFO_COMPONENT_HPP
