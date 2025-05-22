#pragma once

#include <iostream>

namespace input {

struct MouseEvent {
    enum class MouseButton { None, Left, Right, Middle };
    enum class MouseAction { Press, Release };

    int x = 0, y = 0;
    MouseButton button = MouseButton::None;
    MouseAction action = MouseAction::Press;
};

void init();

void shutdown();

void update_key_state();

bool poll_input(char& key, bool& got_key, MouseEvent& mouse_event, bool& got_mouse);

bool is_key_pressed(char key);

void update_key_state();
}
