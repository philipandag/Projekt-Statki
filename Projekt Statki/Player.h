#pragma once
#include "EnumsAndConst.h"
#include "OtherUseful.h"
#include "Ship.h"

struct Player {
	Ship** ships;
};

Ship** createShips(int carrier, int battleship, int cruiser, int destroyer);