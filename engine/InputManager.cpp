#include "InputManager.hpp"
#include <linux/input.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include <cstring>
#include <stdexcept>
#include "ui/UIManager.hpp"

using namespace engine;


void InputManager::init(const std::string& keyboard_device_path, const std::string& mouse_device_path) {
    keyboardFd_ = open(keyboard_device_path.c_str(), O_RDONLY | O_NONBLOCK);
    if (keyboardFd_ < 0) {
        throw std::runtime_error("No se pudo abrir el dispositivo de entrada: " + keyboard_device_path);
    }
	mouseFd_ = open(mouse_device_path.c_str(), O_RDONLY | O_NONBLOCK);
	
    if (mouseFd_ < 0) {
        throw std::runtime_error("No se pudo abrir el dispositivo de entrada: " + mouse_device_path);
	}
}

void InputManager::shutdown() {
    if (keyboardFd_ >= 0) {
        close(keyboardFd_);
        keyboardFd_ = -1;
    }

    if (mouseFd_ >= 0) {
        close(mouseFd_);
		mouseFd_ = -1;
	};
}

void InputManager::pollKeyboard() {
    if (keyboardFd_ < 0) return;

    struct input_event ev;
    while (read(keyboardFd_, &ev, sizeof(struct input_event)) > 0) {
        if (ev.type == EV_KEY) {
			bool was_pressed = keyState_[ev.code];
			bool is_pressed = (ev.value != 0);

			if (!was_pressed && is_pressed) {
				keyPressedOnce_[ev.code] = true;
			}
        }
        keyState_[ev.code] = (ev.value != 0);  // 1 = key down, 0 = key up
    }
}

void InputManager::pollMouse() {
	if (mouseFd_ < 0) return;

    struct input_event mev;
    ssize_t bytesRead;
	gMouse_.dx = 0;
    gMouse_.dy = 0;

    while ((bytesRead = read(mouseFd_, &mev, sizeof(mev))) > 0) {
        switch (mev.type) {
            case EV_ABS:
                if (mev.code == ABS_X) {
                    gMouse_.dx = (mouseLastX_ >= 0) ? (mev.value - mouseLastX_) : 0;
                    gMouse_.x = mev.value;
                    mouseLastX_ = mev.value;
                } else if (mev.code == ABS_Y) {
                    gMouse_.dy = (mouseLastY_ >= 0) ? (mev.value - mouseLastY_) : 0;
                    gMouse_.y = mev.value;
                    mouseLastY_ = mev.value;
                }
                break;

            case EV_REL:
                if (mev.code == REL_X) {
                    gMouse_.dx = mev.value;
                    gMouse_.x += mev.value;
                } else if (mev.code == REL_Y) {
                    gMouse_.dy = mev.value;
                    gMouse_.y += mev.value;
                } else if (mev.code == REL_WHEEL) {
                    gMouse_.scrollVertical += mev.value;
                } else if (mev.code == REL_HWHEEL) {
                    gMouse_.scrollHorizontal += mev.value;
                }
                break;

            case EV_KEY:
                switch (mev.code) {
                    case BTN_LEFT:
                        gMouse_.leftPressed = (mev.value == 1);
                        break;
                    case BTN_RIGHT:
                        gMouse_.rightPressed = (mev.value == 1);
                        break;
                    case BTN_MIDDLE:
                        gMouse_.middlePressed = (mev.value == 1);
                        break;
                }
                break;

            default:
                break;
        }
    }
}

bool InputManager::isKeyPressed(int key_code) {
    auto it = keyState_.find(key_code);
    return it != keyState_.end() && it->second;
}

bool InputManager::isKeyPressedOnce(int key_code) {
    auto it = keyPressedOnce_.find(key_code);
    if (it != keyPressedOnce_.end() && it->second) {
        keyPressedOnce_[key_code] = false; // Consume el evento one-shot
        return true;
    }
    return false;
}

void InputManager::resetMouseScroll() {
    gMouse_.scrollVertical = 0;
    gMouse_.scrollHorizontal = 0;
}


