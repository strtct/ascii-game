#ifndef PLAYER_INFO_COMPONENT_HPP
#define PLAYER_INFO_COMPONENT_HPP

#include "engine/ui/ui_component.hpp"
#include "player.hpp"
#include "engine/ui/rect.hpp"
using ui::UIComponent;

class PlayerInfoComponent : public UIComponent {
public:
    PlayerInfoComponent(int x, int y, int width, int height, const Player& player);

    int getX() const override;
    int getY() const override;
    int getWidth() const override;
    int getHeight() const override;
	Rect getBounds() const override;
    void draw() const override;
	void resize(int newWidth, int newHeight) override;

private:
    int x, y, width, height;
    const Player& player;
};


#endif // PLAYER_INFO_COMPONENT_HPP
