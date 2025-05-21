#ifndef UI_MANAGER_HPP
#define UI_MANAGER_HPP

#include <string>
#include <deque>

namespace ui {

void init();
void shutdown();

void log(const std::string& message);
void draw_log_panel();

void add_log(const std::string& message);
void on_mouse_click(int x, int y);


} // namespace ui

#endif

