#ifndef LOG_COMPONENT_HPP
#define LOG_COMPONENT_HPP

#include "engine/ui/ui_component.hpp"
#include <deque>
#include <string>
#include "engine/ui/rect.hpp"

class LogComponent : public ui::UIComponent {
public:
    LogComponent(int x, int y, int width, int height, int zindex, int vindex, const std::deque<std::string>& log_buffer) : UIComponent (x, y, width, height, zindex, vindex), log_buffer_(log_buffer){}
    UIType getType() const override { return UIType::Blocking; }
    void draw() const override;
	void resize(int newWidth, int newHeight) override;
private:
    const std::deque<std::string>& log_buffer_;
};


#endif // LOG_COMPONENT_HPP
