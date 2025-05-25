#ifndef ASCII_RENDERER_HPP
#define ASCII_RENDERER_HPP

#include <string>
#include "color.hpp"
#include "cell.hpp"
namespace ascii {
	
	extern int WIDTH;
	extern int HEIGHT;
		//int get_terminal_width();
	//int get_terminal_height();
	void update_terminal_size();

	void init();
	void shutdown();
	void clear();
	void draw_char(int x, int y, char c, const std::string& color = Color::RESET);
	void draw_text(int x, int y, const std::string& text, const std::string& color = Color::RESET);
	void render();
	

} // namespace ascii

#endif
