#pragma once
#include "EnumsAndConst.h"
#include "OtherUseful.h"
#include<cstdio>
#include<cstdlib>

struct Ship {
	ShipType type;
	int x;
	int y;
	Compass direction;
	PartState part[maxShipLength];
};

void setShip(Ship* ship, int x, int y, Compass direction);