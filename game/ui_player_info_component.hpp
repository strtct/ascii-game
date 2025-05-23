#ifndef PLAYER_INFO_COMPONENT_HPP
#define PLAYER_INFO_COMPONENT_HPP

#include "engine/ui/ui_component.hpp"
#include "player.hpp"
#include "engine/ui/rect.hpp"
#include "engine/ui/ui_type.hpp"

using ui::UIComponent;

class PlayerInfoComponent : public UIComponent {
public:
    PlayerInfoComponent(int x, int y, int vindex, int width, int height, const Player& player);

    int getX() const override;
    int getY() const override;
    int getWidth() const override;
    int getHeight() const override;
	Rect getBounds() const override;
    void draw() const override;
	void resize(int newWidth, int newHeight) override;
    UIType getType() const override { return UIType::Blocking; }

private:
    int x, y, vindex,width, height;
    const Player& player;
};


#endif // PLAYER_INFO_COMPONENT_HPP
