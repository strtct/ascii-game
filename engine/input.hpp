#ifndef INPUT_HPP
#define INPUT_HPP

#include <string>

namespace input {

	struct MouseState {
    	int x = 0;
	    int y = 0;
	    int dx = 0;
	    int dy = 0;

	    bool leftPressed = false;
	    bool rightPressed = false;
	    bool middlePressed = false;

	    int scrollVertical = 0;   // +1 = up, -1 = down
    	int scrollHorizontal = 0; // +1 = right, -1 = left
};

// Inicializa el sistema de entrada abriendo el dispositivo de forma segura usando logind
void init(const std::string& keyboard_device_path, const std::string& mouse_device_path);

// Libera recursos (cierra el file descriptor y el bus D-Bus)
void shutdown();

// Lee eventos desde el dispositivo de entrada y actualiza el estado de teclas
extern MouseState g_mouse;

void poll_keyboard();
void poll_mouse();

// Retorna true si la tecla está actualmente presionada
bool isKeyPressed(int key_code);
bool isKeyPressedOnce(int key_code);
void reset_mouse_scroll();
} // namespace input

#endif // INPUT_HPP
