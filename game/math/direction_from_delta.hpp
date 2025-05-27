#include <cmath>
#include "world/Direction.hpp"
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
namespace math {

	Position getDirectionFromDelta(int mousex, int mousey, int playerx, int playery, int offsetX, int offsetY) {
		int mouseworldx = mousex + offsetX;
		int mouseworldy = mousey + offsetY;
		int dx = mouseworldx - playerx;
		int dy = mouseworldy - playery;

		// Si delta es cero, no cambiamos la dirección (o dejamos la actual)
		if (dx == 0 && dy == 0) return game::world::directions[0];

		// Convertimos a float para calcular ángulo
		float angle = std::atan2(dy, dx); // atan2(dy, dx) devuelve ángulo en radianes entre -pi y pi

		// Normalizamos el ángulo de 0 a 2*pi
		if (angle < 0) angle += 2 * M_PI;

		// Dividimos el círculo en 8 sectores (cada uno de pi/4 radianes)
		int sector = static_cast<int>((angle + M_PI/8) / (M_PI / 4)) % 8;
    	return game::world::directions[sector];
};
}
