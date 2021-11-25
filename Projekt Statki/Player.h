#pragma once
#include "Ship.h"


//const int PlayerMaxCAR = 1;
//const int PlayerMaxBAT = 2;
//const int PlayerMaxCRU = 3;
//const int PlayerMaxDES = 4;

typedef enum
{
	A = 0,
	B = 1,
	BOTH,
	P_STATE,
	P_NONE
}PlayerId;



struct Player 
{
	int maxShips[TypesOfShips] = { 1, 2, 3, 4 };
	Ship** ships;
	Bool allPlaced;
	Bool canShoot;
	int shipPartsLeft;

	int positionY1;
	int positionX1;
	int positionY2;
	int positionX2;
};


Player* createPlayer();

Bool setFleet(Player* player, int car, int bat, int cru, int des);

int countShipParts(Player* player);

Bool allShipsPlaced(Player* player);

void setStartingBoundary(Player* player, int y1, int x1, int y2, int x2);

