#ifndef LOG_COMPONENT_HPP
#define LOG_COMPONENT_HPP

#include "engine/ui/ui_component.hpp"
#include <deque>
#include <string>
#include "engine/ui/rect.hpp"

class LogComponent : public ui::UIComponent {
public:
    LogComponent(int x, int y, int vindex, int width, int height, const std::deque<std::string>& log_buffer);
    int getX() const {return x;};
    int getY() const {return y;};
    int getWidth() const {return width;};
    int getHeight() const {return height;};
	Rect getBounds() const override;
    UIType getType() const override { return UIType::Blocking; }
    void draw() const override;
	void resize(int newWidth, int newHeight) override;
private:
    int x, y, vindex, width, height;
    const std::deque<std::string>& log_buffer_;
};


#endif // LOG_COMPONENT_HPP
