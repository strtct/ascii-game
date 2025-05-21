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
        	for (size_t j = 0; j < line.size() && j < ascii::WIDTH; ++j) {
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

} // namespace ui

