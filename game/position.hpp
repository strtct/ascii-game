#pragma once

struct Position {
    int x;
    int y;
	float z;

	Position() : x(0), y(0), z(0.0f) {}
	Position(int x_, int y_, float z_ = 0.0f) : x(x_), y(y_), z(z_) {}

	Position operator+(const Position& other) const {
        return {x + other.x, y + other.y , z + other.z};
    }

    bool operator==(const Position& other) const {
        return x == other.x && y == other.y && z == other.z;
    }
};
