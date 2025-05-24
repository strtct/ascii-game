#include "ui_log_component.hpp"
#include "engine/ascii_renderer.hpp"
#include <algorithm>
#include "engine/ui/ui_manager.hpp"

//namespace ui {

void LogComponent::resize(int newWidth, int newHeight) {
    width_ = newWidth;
    y_ = newHeight - vindex_; 
}

void LogComponent::draw() const {

	// Dibujar bordes
    for (int xPos = x_; xPos < x_ + width_; ++xPos) {
        ascii::draw_char(xPos, y_, '-');                         
        ascii::draw_char(xPos, y_ + height_ - 1, '-');
    }

    for (int yPos = y_; yPos < y_ + height_; ++yPos) {
        ascii::draw_char(x_, yPos, '|');
        ascii::draw_char(x_ + width_ - 1, yPos, '|');
    }
    // Esquinas
    ascii::draw_char(x_, y_, '+');
    ascii::draw_char(x_ + width_ - 1, y_, '+');
    ascii::draw_char(x_, y_ + height_ - 1, '+');
    ascii::draw_char(x_ + width_ - 1, y_ + height_ - 1, '+');

    // Mostrar las 3 últimas líneas del log_buffer (o menos si no hay tantas)
	// Espacio disponible entre bordes (-2)
    int visible_lines = height_ -2;
    int total_lines = static_cast<int>(log_buffer_.size());

    int start_index = std::max(0, total_lines - visible_lines);
    int draw_line = y_ + 1;

    for (int i = start_index; i < total_lines; ++i) {
        std::string line = log_buffer_[i];

        // Recorta el texto si es más largo que el ancho disponible
        if (line.length() > static_cast<size_t>(width_ - 2)) {
            line = line.substr(0, width_ - 2);
        }

        ascii::draw_text(x_ + 1, draw_line++, line);
    }
}
