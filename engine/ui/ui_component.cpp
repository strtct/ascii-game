#include "rect.hpp"
#include "../ascii_renderer.hpp"
#include "ui_component.hpp"
namespace ui {
void UIComponent::clearArea() const {
	for (int y = getY(); y < getY() + getHeight(); ++y) {
    	for (int x = getX(); x < getX() + getWidth(); ++x) {
        	ascii::draw_char(x, y, ' ');
        }
    }
}
}

