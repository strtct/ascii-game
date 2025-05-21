#ifndef LOG_COMPONENT_HPP
#define LOG_COMPONENT_HPP

#include "engine/ui/ui_component.hpp"
#include <deque>
#include <string>

namespace ui {

class LogComponent : public UIComponent {
public:
    LogComponent(const std::deque<std::string>& log_buffer);

    int getX() const override;
    int getY() const override;
    int getWidth() const override;
    int getHeight() const override;

    void draw() const override;

private:
    int x, y, width, height;
    const std::deque<std::string>& log_buffer_;
};

} // namespace ui

#endif // LOG_COMPONENT_HPP
