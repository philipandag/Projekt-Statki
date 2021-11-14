#include "Ship.h"

void setShip(Ship* ship, int x, int y, Compass direction)
{

	ship->x = x;
	ship->y = y;
	ship->direction = direction;
}