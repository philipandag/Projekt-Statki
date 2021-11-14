#include "Ship.h"
#include "Board.h"

Ship** createShips(int carrier, int battleship, int cruiser, int destroyer)
{
	// there are 4 types of ships
	Ship** ships = (Ship**)malloc(sizeof(Ship*) * 4);
	ships[0] = (Ship*)malloc(sizeof(Ship) * carrier);
	for (int i = 0; i < carrier; i++)
		ships[0][i].type = CAR;
	ships[1] = (Ship*)malloc(sizeof(Ship) * battleship);
	for (int i = 0; i < battleship; i++)
		ships[1][i].type = BAT;
	ships[2] = (Ship*)malloc(sizeof(Ship) * cruiser);
	for (int i = 0; i < cruiser; i++)
		ships[2][i].type = CRU;
	ships[3] = (Ship*)malloc(sizeof(Ship) * destroyer);
	for (int i = 0; i < destroyer; i++)
		ships[3][i].type = DES;
	return ships;
}
