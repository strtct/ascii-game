#ifndef INPUT_MANAGER_HPP
#define INPUT_MANAGER_HPP

#include <string>
#include <map>

namespace engine {	
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

	class InputManager {
		public:
			InputManager() {
				keyboardFd_ = -1;
				mouseFd_ = -1;
				mouseLastX_ = -1;
				mouseLastY_ = -1;
			}
            
            static InputManager& getInstance() {
                static InputManager instance;
                return instance;
            }

			// Getters
			int getMouseX() const { return gMouse_.x; }
			int getMouseY() const { return gMouse_.y; }
			MouseState getMouseState() const { return gMouse_; }

			// Inicializa el sistema de entrada abriendo el dispositivo de forma segura usando logind
			void init(const std::string& keyboard_device_path, const std::string& mouse_device_path);

			// Libera recursos (cierra el file descriptor y el bus D-Bus)
			void shutdown();
            static void shutdownStatic() {
                getInstance().shutdown();
            }
			void pollKeyboard();
			void pollMouse();

			// Retorna true si la tecla está actualmente presionada
			bool isKeyPressed(int key_code);
			bool isKeyPressedOnce(int key_code);

			void resetMouseScroll();
    
		private:
			MouseState gMouse_;
			std::map<int, bool> keyState_, prevKeyState_, keyPressedOnce_;
			int keyboardFd_, mouseFd_, mouseLastX_, mouseLastY_;
    };
} // namespace input

#endif // INPUT_HPP
