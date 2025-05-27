#include "Rect.hpp"
#include "UIComponent.hpp"

using namespace engine::ui;

void UIComponent::clearArea(Renderer& renderer) const {
	for (int y = getY(); y < getY() + getHeight(); ++y) {
    	for (int x = getX(); x < getX() + getWidth(); ++x) {
        	renderer.drawChar(x, y, ' ');
        }
    }
}


