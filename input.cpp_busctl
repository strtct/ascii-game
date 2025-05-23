#include "input.hpp"
#include <linux/input.h>
#include <fcntl.h>
#include <unistd.h>
#include <string>
#include <cstring>
#include <map>
#include <stdexcept>
#include <systemd/sd-login.h>
#include <systemd/sd-bus.h>
#include <iostream>
#include <sys/stat.h>
#include <sys/sysmacros.h>

namespace input {

static std::map<int, bool> key_state;
static int input_fd = -1;
static sd_bus* bus = nullptr;


void init(const std::string& device_path) {
    int r = sd_bus_open_system(&bus);
    if (r < 0) {
        throw std::runtime_error("No se pudo conectar al bus del sistema: " + std::string(strerror(-r)));
    }

    char* session = nullptr;
    r = sd_pid_get_session(0, &session);
    if (r < 0) {
        throw std::runtime_error("No se pudo obtener la sesión actual: " + std::string(strerror(-r)));
    }

    // Obtener la ruta del objeto de sesión desde el nombre
    sd_bus_message* reply = nullptr;
    sd_bus_error error = SD_BUS_ERROR_NULL;
    r = sd_bus_call_method(
        bus,
        "org.freedesktop.login1",
        "/org/freedesktop/login1",
        "org.freedesktop.login1.Manager",
        "GetSession",
        &error,
        &reply,
        "s",
        session
    );
    if (r < 0) {
        throw std::runtime_error("No se pudo obtener el objeto de la sesión: " + std::string(error.message));
    }

    const char* session_path = nullptr;
    r = sd_bus_message_read(reply, "o", &session_path);
    if (r < 0) {
        throw std::runtime_error("No se pudo leer la ruta de la sesión: " + std::string(strerror(-r)));
    }

    // Intentar tomar control de la sesión
    sd_bus_message* control_reply = nullptr;
    sd_bus_error control_error = SD_BUS_ERROR_NULL;
    r = sd_bus_call_method(
        bus,
        "org.freedesktop.login1",
        session_path,
        "org.freedesktop.login1.Session",
        "TakeControl",
        &control_error,
        &control_reply,
        "b",  // parámetro booleano: force (true para forzar el control)
        1     // true
    );
    if (r < 0) {
        throw std::runtime_error("No se pudo tomar el control de la sesión: " + std::string(control_error.message));
    }
    sd_bus_message_unref(control_reply);

    // Obtener major y minor desde stat()
    struct stat st;
    if (stat(device_path.c_str(), &st) < 0) {
        throw std::runtime_error("stat falló en " + device_path);
    }
    unsigned major_num = major(st.st_rdev);
    unsigned minor_num = minor(st.st_rdev);

    std::cout << "session_path " << session_path << std::endl
              << "minor: " << minor_num << " major: " << major_num << std::endl;

    // Llamar a TakeDevice
    sd_bus_message* m = nullptr;
    r = sd_bus_call_method(
        bus,
        "org.freedesktop.login1",
        session_path,
        "org.freedesktop.login1.Session",
        "TakeDevice",
        &error,
        &m,
        "uu",
        major_num,
        minor_num
    );
    free(session);

    if (r < 0) {
        throw std::runtime_error("Error al llamar a TakeDevice: " + std::string(error.message));
    }

    int fd = -1;
    r = sd_bus_message_read(m, "h", &fd);
    if (r < 0) {
        throw std::runtime_error("Error al leer file descriptor: " + std::string(strerror(-r)));
    }

    input_fd = fd;
    sd_bus_message_unref(m);
}
void shutdown() {
    if (input_fd >= 0) {
        close(input_fd);
        input_fd = -1;
    }
    if (bus) {
        sd_bus_unref(bus);
        bus = nullptr;
    }
}

void poll() {
    if (input_fd < 0) return;

    struct input_event ev;
    while (read(input_fd, &ev, sizeof(struct input_event)) > 0) {
        if (ev.type == EV_KEY) {
            key_state[ev.code] = (ev.value != 0);  // 1 = pulsada, 0 = liberada
        }
    }
}

bool isKeyPressed(int key_code) {
    auto it = key_state.find(key_code);
    return it != key_state.end() && it->second;
}

} // namespace input
