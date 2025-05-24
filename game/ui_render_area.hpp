#pragma once
#include "engine/ui/ui_component.hpp"
#include "engine/ui/ui_type.hpp"
class RenderAreaComponent : public ui::UIComponent {
public:
    RenderAreaComponent(int x, int y, int width, int height, int zindex, int vindex)
        : UIComponent(x, y, width, height, zindex, vindex) {}


    void draw() const override {}  // No dibuja nada

    void resize(int newWidth, int newHeight) {
        width_ = newWidth;
        y_ = newHeight - vindex_;
    }

    UIType getType() const override { return UIType::RenderArea; }

};
