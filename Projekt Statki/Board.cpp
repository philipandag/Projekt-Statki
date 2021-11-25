#include "Board.h"
#include <stdlib.h>
#include <stdio.h>

Board* createBoard(int y, int x)
{
	if (x > 0 && y > 0)
	{
		Board* board = (Board*)malloc(sizeof(Board));

		board->fields = (char**)malloc(sizeof(char*) * y);
		for (int i = 0; i < y; i++)
		{
			board->fields[i] = (char*)malloc(sizeof(char) * x);
			for (int j = 0; j < x; j++)
			{
				board->fields[i][j] = FIELD_EMPTY;
			}
		}


		board->sizeY = y;
		board->sizeX = x;

		return board;
	}
	return NULL;
}

void printBoard(Board* board, int mode, GameLogic logic, Player** players, PlayerId playerId)
{
	int xIndexLength = intLength(board->sizeX, BaseX);
	int yIndexLength = intLength(board->sizeY, BaseY);
	printf("\n");
	if (mode == 1)
	{
		for (int y = -xIndexLength; y < board->sizeY; y++)
		{
			for (int x = -yIndexLength; x < board->sizeX; x++)
			{
				if (y < 0)
				{
					if (x < 0)
					{
						printf(" "); //Róg planszy - pusty
					}
					else
					{
						//Indexy X - Z góry
						char index;
						index = (x / power10(-y - 1)) % BaseX + '0'; //Oddzielenie liczb dziesi¹tek od jednoœci
						printf("%c", index);
					}
				}
				else if (x < 0)
				{
					// Indeksy Y - z lewej
					char index;
					index = (y / power10(-x - 1)) % BaseY + '0';
					printf("%c", index);
				}
				else
				{
					//Plansza w³aœciwa
					if (y < board->sizeY && x < board->sizeX)
						printf("%c", board->fields[y][x]);
				}
				if (x == -1)
					printf(" ");
			}
			if (y == -1)
				printf("\n");
			printf("\n");
		}
		printf("PARTS REMAINING:: A : %d B : %d\n", players[A]->shipPartsLeft, players[B]->shipPartsLeft);
	}
	else if (mode == 0)
	{
		for (int y = 0; y < board->sizeY; y++)
		{
			for (int x = 0; x < board->sizeX; x++)
			{
				printf("%c", changeToBasicField(board->fields[y][x]) );
			}
			printf("\n");
		}	
		if(players[A]->shipPartsLeft > 0 || players[B]->shipPartsLeft > 0)
			printf("PARTS REMAINING:: A : %d B : %d\n", players[A]->shipPartsLeft, players[B]->shipPartsLeft);
	}
	
}
char changeToBasicField(char field)
{
	if (field == '%' || field == '@' || field == '!')
		field = '+';

	return field;
}
Bool isShipInPlayersStartingPosition(Player* player, Ship* ship)
{
	Bool correctMove = True;
	switch (ship->direction)
	{
	case N: //FACING Y-
		for (int i = 0; i < ship->length; i++)
			if (withinArea(player->positionY1, player->positionX1, player->positionY2, player->positionX2, ship->y + i, ship->x) == False)
			{
				correctMove = False;
				break;
			}
		break;
	case S: //FACING Y+
		for (int i = 0; i < ship->length; i++)
			if (withinArea(player->positionY1, player->positionX1, player->positionY2, player->positionX2, ship->y - i, ship->x) == False)
			{
				correctMove = False;
				break;
			}
		break;
	case E: //FACING X+
		for (int i = 0; i < ship->length; i++)
			if (withinArea(player->positionY1, player->positionX1, player->positionY2, player->positionX2, ship->y, ship->x - i) == False)
			{
				correctMove = False;
				break;
			}
		break;
	case W: //FACING X-
		for (int i = 0; i < ship->length; i++)
			if (withinArea(player->positionY1, player->positionX1, player->positionY2, player->positionX2, ship->y, ship->x + i) == False)
			{
				correctMove = False;
				break;
			}
		break;
	}

	return correctMove;	
}
Bool onBoard(Board* board, int y, int x)
{
	return withinArea(0, 0, board->sizeY - 1, board->sizeX - 1, y, x);
}
Bool withinArea(int Ay1, int Ax1, int Ay2, int Ax2, int y, int x)
{
	if ( (Ax1 <= x && x <= Ax2) && (Ay1 <= y && y <= Ay2) )
		return True;
	else
		return False;
}
Bool onShip(Player** players, int y, int x)
{
	for(int p = 0; p <= 1; p++)
		for (int type = 0; type < TypesOfShips; type++)
		{
			for (int id = 0; id < players[p]->maxShips[type]; id++)
			{
				switch (players[p]->ships[type][id].direction)
				{
				case N:
					for (int i = 0; i < players[p]->ships[type][id].length; i++)
						if (players[p]->ships[type][id].y - i == y && players[p]->ships[type][id].x == x)
						{
							return True;
						}
				}
			}
		}
	return False;
}

Bool shootThatShip(Board* board, Ship* ship, int partId)
{
	Bool didHit = False;
	//Ship pendingShip = player->ships[type][id];
	Ship pendingShip = *ship;

	//createShip(&pendingShip, static_cast<ShipType>(type), player->ships[type][id].y, player->ships[type][id].x, player->ships[type][id].direction, False, player->ships[type][id].part, player->ships[type][id].shipOnline, player->ships[type][id].placed);
	if (pendingShip.part[partId] != PART_DESTROYED)
		didHit = True;
	pendingShip.part[partId] = PART_DESTROYED;
	updateShip(board, ship, &pendingShip);
	*ship = pendingShip;

	return didHit;
}
Bool tryToShoot(Board* board, Player* player, int type, int id, int y, int x, int xDir, int yDir, int partId)
{
	if ((player->ships[type][id].y + partId*yDir == y) && (player->ships[type][id].x + partId*xDir == x))
	{
		if (shootThatShip(board, &player->ships[type][id], partId))
			player->shipPartsLeft--;
	}
	return True;
}

Bool shootShip(Board* board, Player** players, int y, int x)
{
	for (int p = 0; p <= 1; p++)
		for (int type = 0; type < TypesOfShips; type++)
			for (int id = 0; id < players[p]->maxShips[type]; id++)
				switch (players[p]->ships[type][id].direction)
				{
				case N: // Facing Y-
					for (int i = 0; i < players[p]->ships[type][id].length; i++)
						if ( (players[p]->ships[type][id].y + i == y) && (players[p]->ships[type][id].x == x) )
							tryToShoot(board, players[p], type, id, y, x, 0, 1, i);						
					break;
				case S: // Facing Y+
					for (int i = 0; i < players[p]->ships[type][id].length; i++)
						if (players[p]->ships[type][id].y - i == y && players[p]->ships[type][id].x == x)
							tryToShoot(board, players[p], type, id, y, x, 0, -1, i);						
					break;
				case E: // Facing X+
					for (int i = 0; i < players[p]->ships[type][id].length; i++)
						if (players[p]->ships[type][id].y == y && players[p]->ships[type][id].x - i == x)
							tryToShoot(board, players[p], type, id, y, x, -1, 0, i);			
					break;
				case W: // Facing X-
					for (int i = 0; i < players[p]->ships[type][id].length; i++)
						if (players[p]->ships[type][id].y == y && players[p]->ships[type][id].x + i == x)
							tryToShoot(board, players[p], type, id, y, x, 1, 0, i);
					break;
				default:
					return False;
				}
	return False;
}
void deleteShip(Board* board, Ship* ship)
{
	drawShip(board, ship, FIELD_EMPTY);
	ship->shipOnline = False;
}
void drawShip(Board* board, Ship* ship, Field piece)
{
	switch (ship->direction)
	{
	case N: //Facing Y-, draw in Y+
		for (int i = 0; i < ship->length; i++)
			setBoardField(board, ship->y + i, ship->x, piece == FIELD_SHIP ? ship->part[i] : piece);
		//board->fields[ship->y + i][ship->x] = FIELD_EMPTY;
		break;
	case S: //Facing Y+, draw in Y-
		for (int i = 0; i < ship->length; i++)
			setBoardField(board, ship->y - i, ship->x, piece == FIELD_SHIP ? ship->part[i] : piece);
		//board->fields[ship->y - i][ship->x] = FIELD_EMPTY;
		break;
	case E: //Facing X+, draw in X-
		for (int i = 0; i < ship->length; i++)
			setBoardField(board, ship->y, ship->x - i, piece == FIELD_SHIP ? ship->part[i] : piece);
		//board->fields[ship->y][ship->x - i] = FIELD_EMPTY;
		break;
	case W: //Facing X-, draw in X+
		for (int i = 0; i < ship->length; i++)
			setBoardField(board, ship->y, ship->x + i, piece == FIELD_SHIP ? ship->part[i] : piece);
		//board->fields[ship->y][ship->x + i] = FIELD_EMPTY;
		break;
	}
}

void placeShip(Board* board, Ship* ship)
{
	//if (checkShipPositionBoard(board, ship) == False)
	//	return;
	drawShip(board, ship, FIELD_SHIP);
}
inline Field partToField(ShipParts part)
{
	return static_cast<Field>(part);
}
void updateShip(Board* board, Ship* oldShip, Ship* newShip)
{
	deleteShip(board, oldShip);
	placeShip(board, newShip);
}

void setBoardField(Board* board, int y, int x, char piece) 
{
	board->fields[y][x] = piece;
}

Bool placeReef(Board* board, int y1, int x1, int y2, int x2)
{
	if(onBoard(board, y1, x1) && onBoard(board, y2, x2))
		for(int y = y1; y <= y2; y++)
			for (int x = x1; x <= x2; x++)
			{
				if (board->fields[y][x] == FIELD_EMPTY)
					board->fields[y][x] = FIELD_REEF;
				else
					return False;
			}
	return True;
}
Bool checkShipPartTooClose(Board* board, Ship* ship, int xDir, int yDir, int partId)
{
	if (xDir != 0 && yDir != 0)
		return True;

	Bool collides = False;

	int dy = yDir;
	int dx = xDir;

	int dy1 = dy == 0 ? -1 : dy*partId;
	int dy2 = dy == 0 ? 1 : dy*partId;
	int dx1 = dx == 0 ? -1 : dx*partId;
	int dx2 = dx == 0 ? 1 : dx*partId;
	// dy1, dy2 - if oriented horizontally, they equal -1, 1, else dy
	// dx1, dx2 - if oriented vertically, they equal -1, 1, else dx
	if (partId == -1 || partId == ship->length)
	{
		if (onBoard(board, ship->y + dy1, ship->x + dx1) && (board->fields[ship->y + dy1][ship->x + dx1] != FIELD_EMPTY && board->fields[ship->y + dy1][ship->x + dx1] != FIELD_REEF)
			)// Positions in front of and behind the ship
		{
			collides = True;
			//break;
		}
	}
	if (
		partId == -1 && onBoard(board, ship->y - yDir, ship->x - xDir) && (board->fields[ship->y - yDir][ship->x - xDir] != FIELD_EMPTY && board->fields[ship->y - yDir][ship->x - xDir] != FIELD_REEF)
		||
		partId == ship->length && onBoard(board, ship->y + yDir, ship->x + xDir) && (board->fields[ship->y + yDir][ship->x + xDir] != FIELD_EMPTY && board->fields[ship->y + yDir][ship->x + xDir] != FIELD_REEF)
		||
		onBoard(board, ship->y + dy1, ship->x + dx1) && (board->fields[ship->y + dy1][ship->x + dx1] != FIELD_EMPTY && board->fields[ship->y + dy1][ship->x + dx1] != FIELD_REEF)
		||
		onBoard(board, ship->y + dy2, ship->x + dx2) && (board->fields[ship->y + dy2][ship->x + dx2] != FIELD_EMPTY && board->fields[ship->y + dy2][ship->x + dx2] != FIELD_REEF)
		)// ship can only touch EMPTY or REEF, any other field is a ship part
	{
		collides = True;
		//break;
	}

	return collides;
}

Field checkShipPositionBoard(Board* board, Ship* ship)
{
	Field collidesWith = FIELD_EMPTY;
	if (ship->x >= 0 && ship->x < board->sizeX || ship->y >= 0 || ship->y < board->sizeY)
	{
		switch (ship->direction)
		{
		case N://Facing: Y-
			for (int i = 0; i < ship->length; i++) // check colision
			{
				if (board->fields[ship->y + i][ship->x] == FIELD_REEF)
				{
					return FIELD_REEF;
					break;
				}
				if (board->fields[ship->y + i][ship->x] == FIELD_RADAR || board->fields[ship->y + i][ship->x] == FIELD_CANNON || board->fields[ship->y + i][ship->x] == FIELD_SHIP || board->fields[ship->y + i][ship->x] == FIELD_ENGINE)
				{
					return FIELD_SHIP;
					break;
				}
			}
			for (int i = -1; i < ship->length+1; i++) // check if touches other ships
			{
				if (checkShipPartTooClose(board, ship, 0, 1, i))
					return FIELD_SHIP;
			}
			break;

		case S: // FACING Y+
			for (int i = 0; i < ship->length; i++) // check colision
			{
				if (board->fields[ship->y - i][ship->x] != FIELD_EMPTY)
				{
					collidesWith = FIELD_SHIP;
					break;
				}
			}
			for (int i = -1; i < ship->length + 1; i++) // check if touches other ships
			{
				if(checkShipPartTooClose(board, ship, 0, -1, i))
					return FIELD_SHIP;
			}
			break;

		case E: // FACING X+
			for (int i = 0; i < ship->length; i++) // check colision
			{
				if (board->fields[ship->y][ship->x - i] != FIELD_EMPTY)
				{
					collidesWith = FIELD_SHIP;
					break;
				}
			}
			for (int i = -1; i < ship->length + 1; i++) // check if touches other ships
			{
				if(checkShipPartTooClose(board, ship, -1, 0, i))
					return FIELD_SHIP;
			}
			break;

		case W: // FACING X-
			for (int i = 0; i < ship->length; i++) // check colision
			{
				if (board->fields[ship->y][ship->x + i] != FIELD_EMPTY)
				{
					collidesWith = FIELD_SHIP;
					break;
				}
			}
			for (int i = -1; i < ship->length + 1; i++) // check if touches other ships
			{
				if(checkShipPartTooClose(board, ship, 1, 0, i))
					return FIELD_SHIP;
			}
			break;
		}
	}
	else
		collidesWith = FIELD_SHIP;


	return collidesWith;
}