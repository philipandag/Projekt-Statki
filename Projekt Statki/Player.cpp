#include "Player.h"
#include <stdlib.h>

void createShips(Player* player)
{
	player->ships = (Ship**)malloc(sizeof(Ship*) * TypesOfShips);
	Ship** ships = player->ships;

	ships[CAR] = (Ship*)malloc(sizeof(Ship) * MaxShipsOfType);
	for (int i = 0; i < player->maxShips[CAR]; i++)
		createShip(&(ships[CAR][i]), CAR, 0, -2, S, True, NULL, False);

	ships[BAT] = (Ship*)malloc(sizeof(Ship) * MaxShipsOfType);
	for (int i = 0; i < player->maxShips[BAT]; i++)
		createShip(&(ships[BAT][i]), BAT, 0,-2, S, True, NULL, False);

	ships[CRU] = (Ship*)malloc(sizeof(Ship) * MaxShipsOfType);
	for (int i = 0; i < player->maxShips[CRU]; i++)
		createShip(&(ships[CRU][i]), CRU, 0, -2, S, True, NULL, False);

	ships[DES] = (Ship*)malloc(sizeof(Ship) * MaxShipsOfType);
	for (int i = 0; i < player->maxShips[DES]; i++)
		createShip(&(ships[DES][i]), DES, 0, -2, S, True, NULL, False);

}
void setStartingBoundary(Player* player, int y1, int x1, int y2, int x2)
{
	player->positionY1 = y1;
	player->positionX1 = x1;
	player->positionY2 = y2;
	player->positionX2 = x2;
}

void addShip(Player* player, int y, int x, Compass direction, int id, ShipType type)
{

}
