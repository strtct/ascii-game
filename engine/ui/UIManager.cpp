#include "UIManager.hpp"
#include <string>
#include <deque>
#include <iostream>
#include <memory>
#include <algorithm>

using namespace engine::ui;

const std::vector<std::shared_ptr<UIComponent>>& UIManager::getComponents() {
	return components_;
}
	
const std::deque<std::string>& UIManager::getLogBuffer() {
   	return logBuffer_;
}

void UIManager::init() {
   	log("UI Inicializada.");
	components_.clear();
}

void UIManager::shutdown() {
    log("UI Finalizada.");
	components_.clear();
}
	
void UIManager::addComponent(std::shared_ptr<UIComponent> comp) {
	components_.push_back(std::move(comp));
}
	
void UIManager::removeComponent(std::shared_ptr<UIComponent> comp) {
    components_.erase(
        std::remove(components_.begin(), components_.end(), comp),
        components_.end()
    );
}
	
void UIManager::drawAll() {
	std::sort(
		components_.begin(), components_.end(),
			[](const auto& a, const auto& b) {
    	    	return a->getZIndex() < b->getZIndex();
	    }
	);
	for (auto& comp : components_) {
        	comp->draw();
    }
}
	
bool UIManager::isCovered(int x, int y) const {
	for (auto& comp : components_) {
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

void UIManager::log(const std::string& message) {
	if (logBuffer_.size() >= maxLogLines_) logBuffer_.pop_front();
    	logBuffer_.push_back(message);
}

void UIManager::addLog(const std::string& message) {
    log(message);
}

void UIManager::onMouseClick(int x, int y) {
	log("Click (" + std::to_string(x) + ", " + std::to_string(y) + ")");
}

void UIManager::resizeAll(int newWidth, int newHeight) {
	for (auto& comp : components_) {
        comp->resize(newWidth, newHeight);
    }
}
