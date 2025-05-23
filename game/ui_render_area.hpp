#pragma once
#include "engine/ui/ui_component.hpp"
#include "engine/ui/ui_type.hpp"
class RenderAreaComponent : public UIComponent {
public:
    RenderAreaComponent(int x_, int y_, int vindex_, int width_, int height_)
        : x(x_), y(y_), vindex(vindex_), width(width_), height(height_) {
	}

    int getX() const override { return x; }
    int getY() const override { return y; }
    int getWidth() const override { return width; }
    int getHeight() const override { return height; }

    void draw() const override {}  // No dibuja nada

    void resize(int newWidth, int newHeight) {
        width = newWidth;
        y = newHeight - vindex;
    }

    UIType getType() const override { return UIType::RenderArea; }

    Rect getBounds() const override {
        return Rect{x, y, width, height};
    }

private:
    int x, y, vindex, width, height;
};
