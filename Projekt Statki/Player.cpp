#include "Player.h"
#include <stdlib.h>

Player* createPlayer()
{
	Player* player = (Player*)malloc(sizeof(Player));
	for (int i = 0; i < TypesOfShips; i++)
		player->maxShips[i] = i + 1;

	player->ships = (Ship**)malloc(sizeof(Ship*) * TypesOfShips);
	player->canShoot = True;


	player->ships[CAR] = (Ship*)malloc(sizeof(Ship) * MaxShipsMax);
	for (int i = 0; i < player->maxShips[CAR]; i++)
		createShip(&(player->ships[CAR][i]), CAR, 0, -10, S, True, NULL, False, False); //Create unused ship out of the board so that it won't interfere for sure

	player->ships[BAT] = (Ship*)malloc(sizeof(Ship) * MaxShipsMax);
	for (int i = 0; i < player->maxShips[BAT]; i++)
		createShip(&(player->ships[BAT][i]), BAT, 0, -10, S, True, NULL, False, False);

	player->ships[CRU] = (Ship*)malloc(sizeof(Ship) * MaxShipsMax);
	for (int i = 0; i < player->maxShips[CRU]; i++)
		createShip(&(player->ships[CRU][i]), CRU, 0, -10, S, True, NULL, False, False);

	player->ships[DES] = (Ship*)malloc(sizeof(Ship) * MaxShipsMax);
	for (int i = 0; i < player->maxShips[DES]; i++)
		createShip(&(player->ships[DES][i]), DES, 0, -10, S, True, NULL, False, False);

	player->shipPartsLeft = 0;
	player->allPlaced = False;

	return player;
}

void setStartingBoundary(Player* player, int y1, int x1, int y2, int x2)
{
	player->positionY1 = y1;
	player->positionX1 = x1;
	player->positionY2 = y2;
	player->positionX2 = x2;
}

Bool setFleet(Player* player, int car, int bat, int cru, int des)
{
	if( car >= 0 && car <= MaxShipsMax && bat >= 0 && bat <= MaxShipsMax && cru >= 0 && cru <= MaxShipsMax && des >= 0 && des <= MaxShipsMax)
	{
		player->maxShips[CAR] = car;
		player->maxShips[BAT] = bat;
		player->maxShips[CRU] = cru;
		player->maxShips[DES] = des;
		return True;
	}
	return False;
}

int countShipParts(Player* player)
{
	int parts = 0;
	for (int type = 0; type < TypesOfShips; type++)
	{
		for (int id = 0; id < player->maxShips[type]; id++)
		{
			if(player->ships[type][id].placed == True && player->ships[type][id].shipOnline == True)
			for (int p = 0; p < player->ships[type][id].length; p++)
				if (player->ships[type][id].part[p] != PART_DESTROYED)
					parts++;
		}
	}
	return parts;
}
Bool allShipsPlaced(Player* player)
{
	for (int type = 0; type < TypesOfShips; type++)
	{
		for (int id = 0; id < player->maxShips[type]; id++)
		{
			if (player->ships[type][id].placed == False)
				return False;
		}
	}
	return True;
}
