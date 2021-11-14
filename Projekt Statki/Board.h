#pragma once
#include "EnumsAndConst.h"
#include "Ship.h"
#include "OtherUseful.h"
#include <cstdio>
#include <cstdlib>

struct Board {
	int** fields;
	int sizeX;
	int sizeY;
};

Board* createBoard(int y, int x); //returns board pointer

void printBoard(Board* board);

void place1(Board* board, int y, int x, char piece = '&');

void placeShip(Board* board, Ship ship);

int checkShipPositionBoard(Board* board, Ship* ship);

