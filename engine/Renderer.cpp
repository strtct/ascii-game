#include "Renderer.hpp"
#include <iostream>
#include <cstring>
#include <string>
#include <linux/fb.h>
#include <cstdio> 
#ifdef _WIN32
    #include <conio.h>
#else
    #include <unistd.h>
    #include <fcntl.h>
	#include <sys/ioctl.h>
#endif

using namespace engine;

void Renderer::init() {
	updateTerminalSize();
	#ifdef _WIN32
	    hOut_ = GetStdHandle(STD_OUTPUT_HANDLE);
	    DWORD mode = 0;
	    GetConsoleMode(hOut_, &mode);
	    SetConsoleMode(hOut_, mode | ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT);
	#else
	    tcgetattr(STDIN_FILENO, &oldt_);
	    struct termios newt = oldt_;
	    newt.c_lflag &= ~(ICANON | ECHO);
	    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	    fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);
		// Habilita eventos de ratón
	    std::cout << "\033[?1000h" << std::flush;
	#endif
}

void Renderer::shutdown() {
	#ifdef _WIN32
   		// Restaurar consola si es necesario
	#else
   		tcsetattr(STDIN_FILENO, TCSANOW, &oldt_);
		// Desactiva eventos de ratón
    	std::cout << "\033[?1000l" << std::flush;
	#endif
}

void Renderer::clear() {
	Cell empty_cell(' ', Color::RESET);
    for (int y = 0; y < rows_; ++y)
		std::fill(buffer[y].begin(), buffer[y].end(), empty_cell);
}

void Renderer::drawChar(int x, int y, char c, const std::string& color) {
    if (x >= 0 && x < cols_ && y >= 0 && y < rows_)
   	    buffer[y][x] = {c, color};
}

void Renderer::drawText(int x, int y, const std::string& text, const std::string& color) {
    for (size_t i = 0; i < text.size(); ++i) {
       	drawChar(x + i, y, text[i], color);
   	}
}

void Renderer::updateTerminalSize() {
	#ifdef _WIN32
		CONSOLE_SCREEN_BUFFER_INFO csbi;
	    hOut_ = GetStdHandle(STD_OUTPUT_HANDLE);
	    if (GetConsoleScreenBufferInfo(hOut_, &csbi)) {
			cols_ = csbi.srWindow.Right - csbi.srWindow.Left + 1;
			rows_ = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
	    }
	#else
	    struct winsize w;
	    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
		cols_ = w.ws_col;
		rows_ = w.ws_row;
	#endif
		
	// Redimensionar buffer para el nuevo tamaño:
   	buffer.resize(rows_);
   	for (auto& row : buffer) {
        row.resize(cols_, {' ', "\033[0m"});
	}
	clear();
}

void Renderer::render() {
	#ifdef _WIN32
	    COORD coord = {0, 0};
	    SetConsoleCursorPosition(hOut_, coord);
	#else
   		std::cout << "\033[H";
	#endif
		
	std::string last_color="";

   	for (int y = 0; y < rows_; ++y) {
        for (int x = 0; x < cols_; ++x) {
			const Cell& cell = buffer[y][x];
			if (cell.color != last_color) {
       	    	std::cout << cell.color;
				last_color = cell.color;
			}
			std::cout << cell.c;
		}
		if (y < rows_ -1)
	    	std::cout << '\n';
    }
   	std::cout << Color::RESET << std::flush;
}

// Utils methods
int Renderer::getTerminalWidth() const {
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

int Renderer::getTerminalHeight() const {
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

