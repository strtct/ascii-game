#ifndef UI_MANAGER_HPP
#define UI_MANAGER_HPP

#include <string>
#include <deque>
#include <vector>
#include "UIComponent.hpp"
#include "Renderer.hpp"
#include <memory>

namespace engine::ui {

	class UIManager	{
		public:
		    UIManager(Renderer& renderer) : renderer_(renderer), maxLogLines_(5) {
            }
            static UIManager& getInstance() {
                static UIManager instance(engine::Renderer::getInstance());
                return instance;
            }
			void init();
			void shutdown();
            static void shutdownStatic() {
                getInstance().shutdown();
            }
			const std::vector<std::shared_ptr<UIComponent>>& getComponents();
			const std::deque<std::string>& getLogBuffer();
			void addLog(const std::string& message);
			void addComponent(std::shared_ptr<UIComponent> comp);
			void removeComponent(std::shared_ptr<UIComponent> comp);
			void drawAll();
			bool isCovered(int x, int y) const; 
			void onMouseClick(int x, int y);
			void resizeAll(int newWidth, int newHeight);

		private:
			Renderer& renderer_;
			std::deque<std::string> logBuffer_;
			std::vector<std::shared_ptr<UIComponent>> components_;
		    size_t maxLogLines_;
			
			void log(const std::string& message);
	};
} // namespace ui

#endif

