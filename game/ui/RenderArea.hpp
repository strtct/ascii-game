#pragma once
#include "engine/ui/UIComponent.hpp"
#include "engine/ui/ui_type.hpp"

namespace game::ui {
    class RenderAreaComponent : public engine::ui::UIComponent {
        public:
            RenderAreaComponent(int x, int y, int width, int height, int zindex, int vindex, engine::Renderer& renderer)
                : engine::ui::UIComponent(x, y, width, height, zindex, vindex, renderer) {}


            void draw() const override {}  // No dibuja nada

            void resize(int newWidth, int newHeight) {
                width_ = newWidth;
                y_ = newHeight - vindex_;
            }

            UIType getType() const override { return UIType::RenderArea; }

    };
}
