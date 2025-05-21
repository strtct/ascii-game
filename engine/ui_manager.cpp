#include "ui_manager.hpp"
#include "ascii_renderer.hpp"
#include <string>
#include <deque>
#include <iostream>

namespace ui {

	static std::deque<std::string> log_buffer;
	const int MAX_LOG_LINES = 5;

	void init() {
    	log("UI Inicializada.");
	}

	void shutdown() {
    	log("UI Finalizada.");
	}

	void log(const std::string& message) {
    	std::cerr << "message: " << message << std::endl;
	    if (log_buffer.size() >= MAX_LOG_LINES) log_buffer.pop_front();
    	log_buffer.push_back(message);
	}

	void draw_log_panel() {
    	int start_y = ascii::HEIGHT - MAX_LOG_LINES;
	    int i = 0;
    	for (const std::string& line : log_buffer) {
        	for (size_t j = 0; j < line.size() && j < static_cast<size_t>(ascii::WIDTH); ++j) {
            	ascii::draw_char(j, start_y + i, line[j]);
        	}
       		++i;
    	}
	}

	void add_log(const std::string& message) {
    	log(message);
	}

	void on_mouse_click(int x, int y) {
    	std::cerr << "entra en on_mouse_click" << std::endl;
	    log("Click (" + std::to_string(x) + ", " + std::to_string(y) + ")");
	}
	void draw_panel(int x, int y, int width, int height, const std::string& title) {
	    for (int i = 0; i < width; ++i) {
    	    ascii::draw_char(x + i, y, '-');                     // Top border
        	ascii::draw_char(x + i, y + height - 1, '-');        // Bottom border
    	}
   		for (int i = 0; i < height; ++i) {
        	ascii::draw_char(x, y + i, '|');                     // Left border
        	ascii::draw_char(x + width - 1, y + i, '|');         // Right border
    	}

    	ascii::draw_char(x, y, '+');
	    ascii::draw_char(x + width - 1, y, '+');
    	ascii::draw_char(x, y + height - 1, '+');
    	ascii::draw_char(x + width - 1, y + height - 1, '+');

    // Title (centered if it fits)
    	if (!title.empty() && title.size() < static_cast<size_t>(width - 4)) {
        	int titleX = x + (width - title.size()) / 2;
        	ascii::draw_text(titleX, y, title);
   		}
	}

} // namespace ui

