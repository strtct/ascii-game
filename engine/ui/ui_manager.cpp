#include "ui_manager.hpp"
#include "ascii_renderer.hpp"
#include <string>
#include <deque>
#include <iostream>
#include <memory>
#include <algorithm>

namespace ui {

	static std::deque<std::string> log_buffer;
	static std::vector<std::shared_ptr<UIComponent>> components;
	
	const std::vector<std::shared_ptr<UIComponent>>& get_components() {
	    return components;
	}

	const int MAX_LOG_LINES = 5;
	
	const std::deque<std::string>& get_log_buffer() {
    	return log_buffer;
	}

	void init() {
    	log("UI Inicializada.");
		components.clear();
	}

	void shutdown() {
    	log("UI Finalizada.");
		components.clear();
	}
	
	void add_component(std::shared_ptr<UIComponent> comp) {
    	components.push_back(std::move(comp));
	}
	
	void remove_component(std::shared_ptr<UIComponent> comp) {
    	components.erase(
        	std::remove(components.begin(), components.end(), comp),
        	components.end()
    	);
	}
	
	void draw_all() {
	    for (auto& comp : components) {
        	comp->draw();
    	}
	}
	
	bool is_covered(int x, int y) {
	    for (auto& comp : components) {
			if (comp->getType() == UIType::RenderArea) {
	            continue;
    	    }

        	if (comp->getBounds().contains(x, y)) {
            	return true;
        	}

        	//if (comp->getBounds().contains(x, y)) return true;
    	}
    	return false;
	}


	void log(const std::string& message) {
	    if (log_buffer.size() >= MAX_LOG_LINES) log_buffer.pop_front();
    	log_buffer.push_back(message);
	}

	void add_log(const std::string& message) {
    	log(message);
	}

	void on_mouse_click(int x, int y) {
	    log("Click (" + std::to_string(x) + ", " + std::to_string(y) + ")");
	}
	
	void resize_all(int newWidth, int newHeight) {
	    for (auto& comp : components) {
        	comp->resize(newWidth, newHeight);
    	}
	}


} // namespace ui

