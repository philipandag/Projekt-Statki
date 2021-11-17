#pragma once
#include "Player.h"


const int SizeY = 21;
const int SizeX = 10;
const int BaseX = 10; // 0-9
const int BaseY = 10; // a-z


enum Field 
{
	FIELD_EMPTY = ' ',
	FIELD_SHIP = '+',
	FIELD_ENGINE = '%',
	FIELD_CANNON = '!',
	FIELD_RADAR = '@',
	FIELD_DESTROYED = 'x',
	FIELD_REEF = '#'
};

struct Board 
{
	char** fields;
	int sizeX;
	int sizeY;
};

Board* createBoard(int y, int x);



void printBoard(Board* board, int mode, GameLogic logic, Player* players, PlayerId playerId);

char changeToBasicField(char field);

Bool playerShipPlacementFeasible(Player* player, Ship* ship);

Bool onBoard(Board* board, int y, int x);

Bool withinArea(int Ay1, int Ax1, int Ay2, int Ax2, int y, int x);

Bool onShip(Player* players, int y, int x);

Bool shootShip(Board* board, Player* players, int y, int x);

void deleteShip(Board* board, Ship* ship);

void updateShip(Board* board, Ship* oldShip, Ship* newShip);

void place1(Board* board, int y, int x, char piece = '&');

void placeShip(Board* board, Ship* ship);

Bool checkShipPositionBoard(Board* board, Ship* ship);

