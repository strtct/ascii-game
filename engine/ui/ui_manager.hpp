#ifndef UI_MANAGER_HPP
#define UI_MANAGER_HPP

#include <string>
#include <deque>
#include <vector>
#include "ui_component.hpp"
#include <memory>
namespace ui {

void init();
void shutdown();

const std::vector<std::shared_ptr<UIComponent>>& get_components();

void log(const std::string& message);
const std::deque<std::string>& get_log_buffer();

void add_log(const std::string& message);
void add_component(std::shared_ptr<UIComponent> comp);
void remove_component(std::shared_ptr<UIComponent> comp);

void draw_all();

bool is_covered(int x, int y);  // <-- Para usar desde GameWorld u otros


void on_mouse_click(int x, int y);
void resize_all(int newWidth, int newHeight);

} // namespace ui

#endif

