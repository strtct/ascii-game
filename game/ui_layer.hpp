#ifndef UI_LAYER_HPP
#define UI_LAYER_HPP

#include <deque>
#include <string>
#include <memory>
class Player;

namespace ui_layer {

	void init_components(const Player& player, const std::deque<std::string>& log_buffer);


} // namespace ui_layer

#endif // UI_LAYER_HPP
