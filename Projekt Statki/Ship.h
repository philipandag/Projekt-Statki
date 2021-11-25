#pragma once
#include "OtherUseful.h"


const int TypesOfShips = 4;
const int MaxShipsMax = 10;
const int MaxShipLength = 5;

enum ShipType 
{
	CAR = 0,
	BAT = 1,
	CRU = 2,
	DES = 3
};
const int ShipLength[TypesOfShips] = { 5, 4, 3, 2 };

enum ShipParts
{
	PART_NONE = ' ',
	PART_SHIP = '+',
	PART_DESTROYED = 'x',
	PART_RADAR = '@',
	PART_ENGINE = '%',
	PART_CANNON = '!'
	
};

struct Ship 
{
	ShipType type;
	int length;
	int x;
	int y;
	Compass direction;
	ShipParts* part;
	Bool shipOnline;
	Bool placed;
};


void createShip(Ship* ship, ShipType type, int y, int x, Compass direction, Bool newShip, ShipParts* parts, Bool online, Bool placed);
