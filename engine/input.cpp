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
            key_state[ev.code] = (ev.value != 0);  // 1 = key down, 0 = key up
        }
    }
}

bool isKeyPressed(int key_code) {
    auto it = key_state.find(key_code);
    return it != key_state.end() && it->second;
}

} // namespace input
