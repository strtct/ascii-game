#pragma once

#include <iostream>

namespace input {

enum class MouseButton {
    None,
    Left,
    Middle,
    Right
};

enum class MouseAction {
    None,
    Press,
    Release
};

struct MouseEvent {
    MouseButton button = MouseButton::None;
    MouseAction action = MouseAction::None;
    int x = 0;
    int y = 0;
};

// Inicializa terminal en modo raw, no bloqueante, activa seguimiento ratón
void init();

// Restaura terminal y desactiva seguimiento ratón
void shutdown();

// Lee inputs: tecla o evento ratón.
bool poll_input(char& key, bool& got_key, MouseEvent& mouse_event, bool& got_mouse);

}
