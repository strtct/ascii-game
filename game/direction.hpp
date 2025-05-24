#ifndef DIRECTION_HPP
#define DIRECTION_HPP
#include "position.hpp"
namespace Direction {
	enum Direction {
	    UP,
    	UP_RIGHT,
	    RIGHT,
    	DOWN_RIGHT,
	    DOWN,
    	DOWN_LEFT,
	    LEFT,
    	UP_LEFT
	};

	extern const Position directions[8] = {
	    {0, -1, 0},  // UP
	    {1, -1, 0},  // UP_RIGHT
	    {1, 0, 0},   // RIGHT
    	{1, 1, 0},   // DOWN_RIGHT
	    {0, 1, 0},   // DOWN
    	{-1, 1, 0},  // DOWN_LEFT
	    {-1, 0, 0},  // LEFT
    	{-1, -1, 0}  // UP_LEFT
	};
}
#endif
