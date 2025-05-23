#ifndef UI_LAYER_HPP
#define UI_LAYER_HPP

#include <deque>
#include <string>
#include <memory>
#include "engine/ui/rect.hpp"
class RenderAreaComponent;

class Player;

namespace ui_layer {
	
	void init_components(const Player& player, const std::deque<std::string>& log_buffer);
	Rect get_render_area_component();


} // namespace ui_layer

#endif // UI_LAYER_HPP
