#pragma once
#include "Ship.h"


//const int PlayerMaxCAR = 1;
//const int PlayerMaxBAT = 2;
//const int PlayerMaxCRU = 3;
//const int PlayerMaxDES = 4;


enum PlayerId 
{
	A = 0,
	B = 1,
	BOTH = 2
};


struct Player 
{
	int maxShips[TypesOfShips] = { 1, 2, 3, 4 };
	Ship** ships;
	int shipPartsLeft;

	int positionY1;
	int positionX1;
	int positionY2;
	int positionX2;
};


void createShips(Player* player);

void setStartingBoundary(Player* player, int y1, int x1, int y2, int x2);

