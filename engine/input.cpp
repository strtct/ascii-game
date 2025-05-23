#include "input.hpp"
#include <linux/input.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include <cstring>
#include <map>
#include <stdexcept>

namespace input {

static std::map<int, bool> key_state;
static int input_fd = -1;
static std::map<int, bool> prev_key_state;
static std::map<int, bool> key_pressed_once;

void init(const std::string& device_path) {
    input_fd = open(device_path.c_str(), O_RDONLY | O_NONBLOCK);
    if (input_fd < 0) {
        throw std::runtime_error("No se pudo abrir el dispositivo de entrada: " + device_path);
    }
}

void shutdown() {
    if (input_fd >= 0) {
        close(input_fd);
        input_fd = -1;
    }
}

void poll() {
    if (input_fd < 0) return;

    struct input_event ev;
    while (read(input_fd, &ev, sizeof(struct input_event)) > 0) {
        if (ev.type == EV_KEY) {
			bool was_pressed = key_state[ev.code];
			bool is_pressed = (ev.value != 0);

			if (!was_pressed && is_pressed) {
				key_pressed_once[ev.code] = true;
			} else {
				key_pressed_once[ev.code] = false;
			}

            key_state[ev.code] = (ev.value != 0);  // 1 = key down, 0 = key up
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

} // namespace input

