#ifndef LOG_COMPONENT_HPP
#define LOG_COMPONENT_HPP

#include "engine/ui/UIComponent.hpp"
#include <deque>
#include <string>
#include "engine/ui/Rect.hpp"
namespace engine {
    class Renderer;
}
namespace game::ui {
    class LogComponent : public engine::ui::UIComponent {
        public:
            LogComponent(int x, int y, int width, int height, int zindex, int vindex, engine::Renderer& renderer, const std::deque<std::string>& log_buffer) : engine::ui::UIComponent (x, y, width, height, zindex, vindex, renderer), log_buffer_(log_buffer){}
            UIType getType() const override { return UIType::Blocking; }
            void draw() const override;
            void resize(int newWidth, int newHeight) override;

        private:
            const std::deque<std::string>& log_buffer_;
    };
}

#endif // LOG_COMPONENT_HPP
