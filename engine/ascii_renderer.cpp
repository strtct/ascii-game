#include "ascii_renderer.hpp"
#include <iostream>
#include <cstring>
#include <vector>
#include <string>
#include <linux/fb.h>
#include <cstdio> 
#ifdef _WIN32
    #include <conio.h>
    #include <windows.h>
#else
    #include <termios.h>
    #include <unistd.h>
    #include <fcntl.h>
	#include <sys/ioctl.h>
#endif
namespace ascii {
	int WIDTH = 80;
	int HEIGHT = 24;
	
	//static char buffer[HEIGHT][WIDTH];
	static std::vector<std::vector<Cell>> buffer;
	#ifdef _WIN32
		static HANDLE hOut;
	#else
		static struct termios oldt;
	#endif


	int get_terminal_width() {
		#ifdef _WIN32
		    CONSOLE_SCREEN_BUFFER_INFO csbi;
		    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
		    return csbi.srWindow.Right - csbi.srWindow.Left + 1;
		#else
		    struct winsize w;
		    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
		    return w.ws_col;
		#endif
	}
	int get_terminal_height() {
		#ifdef _WIN32
		    CONSOLE_SCREEN_BUFFER_INFO csbi;
		    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
		    return csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
		#else
		    struct winsize w;
		    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
		    return w.ws_row;
		#endif
	}

	void update_terminal_size() {
		#ifdef _WIN32
			CONSOLE_SCREEN_BUFFER_INFO csbi;
		    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
		    if (GetConsoleScreenBufferInfo(hOut, &csbi)) {
    	    	WIDTH = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	    	    HEIGHT = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
		    }
		#else
		    struct winsize w;
		    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
		    WIDTH = w.ws_col;
    		HEIGHT = w.ws_row;
		#endif
		
		// Redimensionar buffer para el nuevo tamaño:
    	buffer.resize(HEIGHT);
    	for (auto& row : buffer) {
	        row.resize(WIDTH, {' ', "\033[0m"});
		}

		clear();
	}


	void init() {
		update_terminal_size();
		
		#ifdef _WIN32
		    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
		    DWORD mode = 0;
		    GetConsoleMode(hOut, &mode);
		    SetConsoleMode(hOut, mode | ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT);
		#else
		    tcgetattr(STDIN_FILENO, &oldt);
		    struct termios newt = oldt;
		    newt.c_lflag &= ~(ICANON | ECHO);
		    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
		    fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);
			// Habilita eventos de ratón
		    std::cout << "\033[?1000h" << std::flush;
		#endif
	}

	void shutdown() {
		#ifdef _WIN32
    		// Restaurar consola si es necesario
		#else
    		tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
			// Desactiva eventos de ratón
	    	std::cout << "\033[?1000l" << std::flush;
		#endif
	}

	void clear() {
		Cell empty_cell(' ', ascii::Color::RESET);
	    for (int y = 0; y < HEIGHT; ++y)
			std::fill(buffer[y].begin(), buffer[y].end(), empty_cell);
	}

	void draw_char(int x, int y, char c, const std::string& color) {
	    if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
    	    buffer[y][x] = {c, color};
	}
	void draw_text(int x, int y, const std::string& text, const std::string& color) {
	    for (size_t i = 0; i < text.size(); ++i) {
        	draw_char(x + i, y, text[i], color);
    	}
	}
	void render() {
			#ifdef _WIN32
		    COORD coord = {0, 0};
		    SetConsoleCursorPosition(hOut, coord);
		#else
    		std::cout << "\033[H";
		#endif
		
		std::string last_color="";

    	for (int y = 0; y < HEIGHT; ++y) {
	        for (int x = 0; x < WIDTH; ++x) {
				const Cell& cell = buffer[y][x];
				if (cell.color != last_color) {
        	    	std::cout << cell.color;
					last_color = cell.color;
				}
				std::cout << cell.c;
			}
			if (y < HEIGHT -1)
   		    	std::cout << '\n';
	    }
    	std::cout << Color::RESET << std::flush;
	}

} // namespace ascii
