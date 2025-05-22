#include "ui_log_component.hpp"
#include "engine/ascii_renderer.hpp"
#include <algorithm>
#include "engine/ui/ui_manager.hpp"

//namespace ui {

LogComponent::LogComponent(int x_, int y_, int vindex_, int width_, int height_, const std::deque<std::string>& log_buffer)
: x(x_), y(y_), vindex(vindex_), width(width_), height(height_), log_buffer_(log_buffer) {
	ui::add_log("log y value: "+std::to_string(y));
}

Rect LogComponent::getBounds() const {
	return Rect{x, y, width, height};
}
	
void LogComponent::resize(int newWidth, int newHeight) {
    width = newWidth;
    y = newHeight - vindex; 
}

void LogComponent::draw() const {

	// Dibujar bordes
    for (int xPos = x; xPos < x + width; ++xPos) {
        ascii::draw_char(xPos, y, '-');                         
        ascii::draw_char(xPos, y + height - 1, '-');
    }

    for (int yPos = y; yPos < y + height; ++yPos) {
        ascii::draw_char(x, yPos, '|');
        ascii::draw_char(x + width - 1, yPos, '|');
    }
    // Esquinas
    ascii::draw_char(x, y, '+');
    ascii::draw_char(x + width - 1, y, '+');
    ascii::draw_char(x, y + height - 1, '+');
    ascii::draw_char(x + width - 1, y + height - 1, '+');

    // Mostrar las 3 últimas líneas del log_buffer (o menos si no hay tantas)
	// Espacio disponible entre bordes (-2)
    int visible_lines = height -2;
    int total_lines = static_cast<int>(log_buffer_.size());

    int start_index = std::max(0, total_lines - visible_lines);
    int draw_line = y + 1;

    for (int i = start_index; i < total_lines; ++i) {
        std::string line = log_buffer_[i];

        // Recorta el texto si es más largo que el ancho disponible
        if (line.length() > static_cast<size_t>(width - 2)) {
            line = line.substr(0, width - 2);
        }

        ascii::draw_text(x + 1, draw_line++, line);
    }
}
