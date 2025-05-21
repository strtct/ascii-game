// ascii_renderer.hpp
#ifndef ASCII_RENDERER_HPP
#define ASCII_RENDERER_HPP

#include <string>

namespace ascii {

const int WIDTH = 80;
const int HEIGHT = 25;

void init();
void shutdown();

void clear();
void draw_char(int x, int y, char c);
void render();
bool poll_input(
    char& key,
    int& mouse_x,
    int& mouse_y,
    bool& left_button,
    bool& got_key,
    bool& got_mouse
);
bool poll_key(char& out);
bool poll_mouse(int& mouse_x, int& mouse_y, bool& left_button);
void draw_text(int x, int y, const std::string& text);

} // namespace ascii

#endif
