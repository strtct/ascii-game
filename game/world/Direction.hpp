#ifndef DIRECTION_HPP
#define DIRECTION_HPP
#include "Position.hpp"
namespace game::world {
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
		{1, 0, 0},   // RIGHT (sector 0)
    {1, 1, 0},   // DOWN_RIGHT (sector 1)
    {0, 1, 0},   // DOWN (sector 2)
    {-1, 1, 0},  // DOWN_LEFT (sector 3)
    {-1, 0, 0},  // LEFT (sector 4)
    {-1, -1, 0}, // UP_LEFT (sector 5)
    {0, -1, 0},  // UP (sector 6)
    {1, -1, 0}   // UP_RIGHT (sector 7)
	};
}
#endif
