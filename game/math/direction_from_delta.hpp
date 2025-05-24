#include "../direction.hpp"
#include <cmath>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
namespace math {

	Position getDirectionFromDelta(int mousex, int mousey, int playerx, int playery) {
		// delta.x, delta.y enteros (ej. diferencia de columnas y filas)
		int dx = mousex - playerx;
		int dy = mousey - playery;

		// Si delta es cero, no cambiamos la dirección (o dejamos la actual)
		if (dx == 0 && dy == 0) return Direction::directions[0];

		// Convertimos a float para calcular ángulo
		float angle = std::atan2(dy, dx); // atan2(dy, dx) devuelve ángulo en radianes entre -pi y pi

		// Normalizamos el ángulo de 0 a 2*pi
		if (angle < 0) angle += 2 * M_PI;

		// Dividimos el círculo en 8 sectores (cada uno de pi/4 radianes)
		int sector = static_cast<int>((angle + M_PI/8) / (M_PI / 4)) % 8;
    	return Direction::directions[sector];
};
}
