#ifndef CELL_HPP
#define CELL_HPP
#include <string>
namespace ascii {
	struct Cell {
    	char c;
	    std::string color;
	
		Cell(char ch = ' ', const std::string& col = "\033[0m")
        	: c(ch), color(col) {}
	};
}
#endif
