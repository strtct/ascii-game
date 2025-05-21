#include "ascii_renderer.hpp"
#include <iostream>
#include <cstring>
#include <vector>
#include <string>

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
	static std::vector<std::vector<char>> buffer;
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
	        row.resize(WIDTH, ' ');
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
	    for (int y = 0; y < HEIGHT; ++y)
			std::fill(buffer[y].begin(), buffer[y].end(), ' ');
	}

	void draw_char(int x, int y, char c) {
	    if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
    	    buffer[y][x] = c;
	}
	void draw_text(int x, int y, const std::string& text) {
	    for (size_t i = 0; i < text.size(); ++i) {
        	draw_char(x + i, y, text[i]);
    	}
	}
	void render() {
		#ifdef _WIN32
		    COORD coord = {0, 0};
		    SetConsoleCursorPosition(hOut, coord);
		#else
    		std::cout << "\033[H";
		#endif

    	for (int y = 0; y < HEIGHT; ++y) {
	        for (int x = 0; x < WIDTH; ++x) {
        	    std::cout << buffer[y][x];
			}
			if (y < HEIGHT -1)
   		    	std::cout << '\n';
	    }
    	std::cout.flush();
	}

	bool poll_input(char& key, int& mouse_x, int& mouse_y, bool& left_button, bool& got_key, bool& got_mouse) {
    	char buf[32];
	    ssize_t n = read(STDIN_FILENO, buf, sizeof(buf));
    	if (n <= 0) {
        	got_key = false;
	        got_mouse = false;
    	    return false;
	    }

    	got_key = false;
	    got_mouse = false;

    	for (ssize_t i = 0; i < n; ++i) {
			if (buf[i] == 27 && i + 5 < n && buf[i+1] == '[' && buf[i+2] == 'M') {
            	// Evento ratón
        	    unsigned char cb = buf[i+3];
    	        unsigned char cx = buf[i+4];
	            unsigned char cy = buf[i+5];
            	left_button = (cb == 32);
        	    mouse_x = cx - 33;
    	        mouse_y = cy - 33;
	            got_mouse = true;
				// Saltar la secuencia de ratón
        	    i += 5;
    	    } else {
	            // Evento teclado simple (carácter ASCII)
            	key = buf[i];
        	    got_key = true;
    	    }
	    }

    	return got_key || got_mouse;
	}

	bool poll_key(char& out) {
		#ifdef _WIN32
		    if (_kbhit()) {
		        out = _getch();
        		return true;
		    }
		    return false;
		#else
		    char ch;

		    if (read(STDIN_FILENO, &ch, 1) == 1) {
        		out = ch;
		        return true;
				std::cout << "dentro";
			}
		    std::cout << "fuera";
    		return false;
		#endif
	}

	bool poll_mouse(int& mouse_x, int& mouse_y, bool& left_button) {
	#ifdef _WIN32
	    // No implementado por simplicidad
    	return false;
	#else
    	char buf[32];
	    ssize_t n = read(STDIN_FILENO, buf, sizeof(buf));
    	if (n <= 0) return false;

	    for (ssize_t i = 0; i < n - 5; ++i) {
    	    if (buf[i] == 27 && buf[i+1] == '[' && buf[i+2] == 'M') {
	            unsigned char cb = buf[i+3];
            	unsigned char cx = buf[i+4];
        	    unsigned char cy = buf[i+5];
    	        left_button = (cb == 32);
	            mouse_x = cx - 33;
            	mouse_y = cy - 33;
        	    return true;
    	    }
	    }
    	return false;
	#endif
	}



} // namespace ascii
