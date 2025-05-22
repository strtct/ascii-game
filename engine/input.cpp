#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <sys/select.h>
#include <unordered_map>
#include <chrono>
#include <iostream>
#include "input.hpp"
namespace input {

// Estado actual (presionado o no)
static std::unordered_map<char, bool> key_state;       
static std::unordered_map<char,std::chrono::steady_clock::time_point> last_press_time;
// timeout tras el que consideramos que se solto una tecla
static constexpr auto release_timeout = std::chrono::milliseconds(400);
static termios original_termios;

void init() {
    termios t;
    tcgetattr(STDIN_FILENO, &original_termios);
    t = original_termios;
    t.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &t);

    int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);
	// activar seguimiento del mouse
    std::cout << "\x1b[?1000h" << std::flush;
}

void shutdown() {
	termios t;
    tcgetattr(STDIN_FILENO, &t);
	t.c_lflag |= (ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &t);
	// desactivar seguimiento del mouse
    std::cout << "\x1b[?1000l" << std::flush;
}

bool is_key_pressed(char key) {
	auto it = key_state.find(key);
    return it != key_state.end() && it->second;
}

bool poll_input(char& key, bool& got_key, MouseEvent& mouse_event, bool& got_mouse) {
    got_key = false;
    got_mouse = false;
    mouse_event = {};

    fd_set set;
    struct timeval timeout = { 0, 0 };
    FD_ZERO(&set);
    FD_SET(STDIN_FILENO, &set);

    int rv = select(STDIN_FILENO + 1, &set, nullptr, nullptr, &timeout);
    if (rv <= 0) return false;

    char buf[6] = {0};
    ssize_t bytes = read(STDIN_FILENO, buf, sizeof(buf));
    if (bytes <= 0) return false;

    // Mouse event ESC [ M cb cx cy
    if (bytes == 6 && buf[0] == 27 && buf[1] == '[' && buf[2] == 'M') {
        unsigned char cb = buf[3];
        unsigned char cx = buf[4];
        unsigned char cy = buf[5];

        int button_code = cb & 0b11;
        bool is_release = cb & (1 << 5);

        mouse_event.x = cx - 33;
        mouse_event.y = cy - 33;
        mouse_event.action = is_release ? MouseEvent::MouseAction::Release : MouseEvent::MouseAction::Press;

        switch (button_code) {
            case 0: mouse_event.button = MouseEvent::MouseButton::Left; break;
            case 1: mouse_event.button = MouseEvent::MouseButton::Middle; break;
            case 2: mouse_event.button = MouseEvent::MouseButton::Right; break;
            default: mouse_event.button = MouseEvent::MouseButton::None; break;
        }

        got_mouse = true;
        return true;
    }

    // Si es una tecla ASCII visible
    if ((unsigned char)buf[0] >= 32 && (unsigned char)buf[0] <= 126) {
        key = buf[0];
        got_key = true;
		auto now = std::chrono::steady_clock::now();

        key_state[key] = true;
		last_press_time[key] = now;
        return true;
    }

    return false;
}


void update_key_state() {

	auto now = std::chrono::steady_clock::now();
    for (auto& [k, pressed] : key_state) {
        if (!pressed) continue;
        if (now - last_press_time[k] > release_timeout) {
            key_state[k] = false;
        }
    }

}

} // namespace input
