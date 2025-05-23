#ifndef INPUT_HPP
#define INPUT_HPP

#include <string>

namespace input {

// Inicializa el sistema de entrada abriendo el dispositivo de forma segura usando logind
void init(const std::string& device_path);

// Libera recursos (cierra el file descriptor y el bus D-Bus)
void shutdown();

// Lee eventos desde el dispositivo de entrada y actualiza el estado de teclas
void poll();

// Retorna true si la tecla está actualmente presionada
bool isKeyPressed(int key_code);
bool isKeyPressedOnce(int key_code);

} // namespace input

#endif // INPUT_HPP
