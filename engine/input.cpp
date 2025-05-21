#include <unistd.h>
#include <vector>
#include <iostream>
#include <termios.h>
#include <fcntl.h>
#include "input.hpp"
namespace input {

static std::vector<char> input_buffer;

void init() {
    // Terminal en modo raw, sin bloqueo
    termios t;
    tcgetattr(STDIN_FILENO, &t);
    t.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &t);

    // STDIN no bloqueante
    int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);

    // Activar seguimiento del ratón
    std::cout << "\x1b[?1000h" << std::flush;
}

void shutdown() {
    // Restaurar terminal
    termios t;
    tcgetattr(STDIN_FILENO, &t);
    t.c_lflag |= (ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &t);

    // Desactivar mouse tracking
    std::cout << "\x1b[?1000l" << std::flush;
}

bool poll_input(char& key,  bool& got_key, MouseEvent& mouse_event, bool& got_mouse) {
    // Leer nuevos datos del stdin si hay
    char buf[64];
    ssize_t n = read(STDIN_FILENO, buf, sizeof(buf));
    if (n > 0) {
        input_buffer.insert(input_buffer.end(), buf, buf + n);
    }

    got_key = false;
    got_mouse = false;
    mouse_event = {};
    // Leer nuevos datos del stdin si hay
    size_t i = 0;
    while (i < input_buffer.size()) {
        // Posible inicio de secuencia de mouse
        if (input_buffer[i] == 27) {
			// Esperar secuencia completa
            if ((i + 5) >= input_buffer.size()) break;

            if (input_buffer[i + 1] == '[' && input_buffer[i + 2] == 'M') {
                unsigned char cb = input_buffer[i + 3];
                unsigned char cx = input_buffer[i + 4];
                unsigned char cy = input_buffer[i + 5];
		int button_code = cb & 0b11;
		bool is_release = cb & (1 << 5);
		mouse_event.x = cx - 33;
		mouse_event.y = cy - 33;
		mouse_event.action = is_release ? MouseAction::Release : MouseAction::Press;
		switch (button_code) {
                    case 0: mouse_event.button = MouseButton::Left; break;
                    case 1: mouse_event.button = MouseButton::Middle; break;
                    case 2: mouse_event.button = MouseButton::Right; break;
                    default: mouse_event.button = MouseButton::None; break;
            }

                got_mouse = true;

                i += 6;
                continue;
            } else {
                // Secuencia no reconocida, descartamos solo ESC
                ++i;
                continue;
            }
        }

        // Tecla imprimible
        if ((unsigned char)input_buffer[i] >= 32 && (unsigned char)input_buffer[i] <= 126) {
            key = input_buffer[i];
            got_key = true;
            ++i;
            continue;
        }

        // Otro byte, no lo reconocemos, descartar
        ++i;
    }

    // Limpiar el buffer procesado
    input_buffer.erase(input_buffer.begin(), input_buffer.begin() + i);

    return got_key || got_mouse;
}

} // namespace input
