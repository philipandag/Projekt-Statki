#include "Ship.h"
#include <stdlib.h>
#include <stdio.h>

void createShip(Ship* ship, ShipType type, int y, int x, Compass direction, Bool newShip, ShipParts* parts, Bool online, Bool placed)
{
	ship->type = type;
	ship->length = ShipLength[type];
	ship->x = x;
	ship->y = y;
	ship->direction = direction;
	ship->part = (ShipParts*)malloc(sizeof(ShipParts) * ShipLength[type]);
	ship->shipOnline = online;
	ship->placed = placed;

	if (newShip == True)
	{
		for (int i = 0; i < ShipLength[type]; i++)
		{
			if (i == 0)
				ship->part[i] = PART_RADAR;
			else if (i == ship->length - 1)
				ship->part[i] = PART_ENGINE;
			else if (i == 1)
				ship->part[i] = PART_CANNON;
			else
				ship->part[i] = PART_SHIP;
		}
	}
	else
	{
		for (int i = 0; i < ShipLength[type]; i++)
		{
			ship->part[i] = parts[i];
		}
	}

}