#include "input.hpp"
#include <linux/input.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include <cstring>
#include <map>
#include <stdexcept>
#include "ui/ui_manager.hpp"
namespace input {

static std::map<int, bool> key_state;
static int keyboard_fd = -1;
static std::map<int, bool> prev_key_state;
static std::map<int, bool> key_pressed_once;

static int mouse_fd = -1;
MouseState g_mouse;
static int last_x = -1;
static int last_y = -1;

void init(const std::string& keyboard_device_path, const std::string& mouse_device_path) {
    keyboard_fd = open(keyboard_device_path.c_str(), O_RDONLY | O_NONBLOCK);
    if (keyboard_fd < 0) {
        throw std::runtime_error("No se pudo abrir el dispositivo de entrada: " + keyboard_device_path);
    }
	mouse_fd = open(mouse_device_path.c_str(), O_RDONLY | O_NONBLOCK);
	
    if (mouse_fd < 0) {
        throw std::runtime_error("No se pudo abrir el dispositivo de entrada: " + mouse_device_path);
	}
}

void shutdown() {
    if (keyboard_fd >= 0) {
        close(keyboard_fd);
        keyboard_fd = -1;
    }

    if (mouse_fd >= 0) {
        close(mouse_fd);
		mouse_fd = -1;
	};
}

void poll_keyboard() {
    if (keyboard_fd < 0) return;

    struct input_event ev;
    while (read(keyboard_fd, &ev, sizeof(struct input_event)) > 0) {
        if (ev.type == EV_KEY) {
			bool was_pressed = key_state[ev.code];
			bool is_pressed = (ev.value != 0);

			if (!was_pressed && is_pressed) {
				key_pressed_once[ev.code] = true;
			}
        }
		ui::add_log("Entra tecla");
        key_state[ev.code] = (ev.value != 0);  // 1 = key down, 0 = key up
    }
}
void poll_mouse() {
	if (mouse_fd < 0) return;

    struct input_event mev;
    ssize_t bytesRead;

    while ((bytesRead = read(mouse_fd, &mev, sizeof(mev))) > 0) {
        switch (mev.type) {
            case EV_ABS:
                if (mev.code == ABS_X) {
                    g_mouse.dx = (last_x >= 0) ? (mev.value - last_x) : 0;
                    g_mouse.x = mev.value;
                    last_x = mev.value;
                } else if (mev.code == ABS_Y) {
                    g_mouse.dy = (last_y >= 0) ? (mev.value - last_y) : 0;
                    g_mouse.y = mev.value;
                    last_y = mev.value;
                }
                break;

            case EV_REL:
                if (mev.code == REL_WHEEL) {
                    g_mouse.scrollVertical += mev.value; // +1: up, -1: down
                } else if (mev.code == REL_HWHEEL) {
                    g_mouse.scrollHorizontal += mev.value; // +1: right, -1: left
                }
                break;

            case EV_KEY:
                switch (mev.code) {
                    case BTN_LEFT:
                        g_mouse.leftPressed = (mev.value == 1);
                        break;
                    case BTN_RIGHT:
                        g_mouse.rightPressed = (mev.value == 1);
                        break;
                    case BTN_MIDDLE:
                        g_mouse.middlePressed = (mev.value == 1);
                        break;
                }
                break;

            default:
                break;
        }
    }
}


bool isKeyPressed(int key_code) {
    auto it = key_state.find(key_code);
    return it != key_state.end() && it->second;
}

bool isKeyPressedOnce(int key_code) {
    auto it = key_pressed_once.find(key_code);
    if (it != key_pressed_once.end() && it->second) {
        key_pressed_once[key_code] = false; // Consume el evento one-shot
        return true;
    }
    return false;
}
void reset_mouse_scroll() {
    g_mouse.scrollVertical = 0;
    g_mouse.scrollHorizontal = 0;
}

} // namespace input

