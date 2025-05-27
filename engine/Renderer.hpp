#ifndef ASCII_RENDERER_HPP
#define ASCII_RENDERER_HPP

#include <string>
#include "Color.hpp"
#include "Cell.hpp"
#include <vector>

#ifdef _WIN32
	#include <windows.h>
#else
	#include <termios.h>
#endif

namespace engine {
	class Renderer {
		public:
			Renderer() {
				rows_ = 80;
				cols_ = 24;
			}

            static Renderer& getInstance() {
                static Renderer instance;
                return instance;
            }
			
			// Getters
			int getCols() const { return cols_; }
			int getRows() const { return rows_; }
			
			// Core logic methods
			void init();
			void shutdown();
            static void shutdownStatic() {
                getInstance().shutdown();
            }
			void clear();
void render();
			void updateTerminalSize();
		
			void drawChar(int x, int y, char c, const std::string& color = Color::RESET);
			void drawText(int x, int y, const std::string& text, const std::string& color = Color::RESET);
		
		private:
			int cols_, rows_;
			std::vector<std::vector<Cell>> buffer;
			#ifdef _WIN32
				HANDLE hOut_;
			#else
				struct termios oldt_;
			#endif
			
			// Utils methods
			int getTerminalWidth() const;
			int getTerminalHeight() const;
	};
} // namespace ascii

#endif
