#pragma once
#include "Player.h"

const int DefaultSizeY = 21;
const int DefaultSizeX = 10;
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
	FIELD_REEF = '#',
	FIELD_OUT_OF_BOARD = '0'
};

struct Board 
{
	Field** fields;
	int sizeX;
	int sizeY;
};

Board* createBoard(int y, int x);



void printBoard(Board* board, int mode, GameLogic logic, Player** players, PlayerId playerId);

char changeToBasicField(char field);

Bool isShipInPlayersStartingPosition(Player* player, Ship* ship);

Bool onBoard(Board* board, int y, int x);

Bool withinArea(int Ay1, int Ax1, int Ay2, int Ax2, int y, int x);

Bool onShip(Player* players, int y, int x);

Bool shootThatShip(Board* board, Player* player, int type, int id, int partId);

Bool tryToShoot(Board* board, Player* player, int type, int id, int y, int x, int xDir, int yDir, int partId);

Bool shootShip(Board* board, Player** players, int y, int x);

void deleteShip(Board* board, Ship* ship);

void drawShip(Board* board, Ship* ship, Field piece);

Field updateShip(Board* board, Ship* oldShip, Ship* newShip);

inline Field partToField(ShipParts part);

void setBoardField(Board* board, int y, int x, char piece);

void placeShip(Board* board, Ship* ship);

Field checkShipPositionBoard(Board* board, Ship* ship);

Field moveShip(Board* board, Ship* ship);

Field rotateShip(Board* board, Ship* ship, char moveDir);

inline Compass rotate(Compass direction, int amount);

inline Field charToField(char c);

