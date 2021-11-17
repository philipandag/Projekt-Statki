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

void printBoard(Board* board, int mode, GameLogic logic, Player* players, PlayerId playerId)
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
		printf("PARTS REMAINING:: A : %d B : %d\n", players[A].shipPartsLeft, players[B].shipPartsLeft);
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
		if(players[A].shipPartsLeft > 0 || players[B].shipPartsLeft > 0)
			printf("PARTS REMAINING:: A : %d B : %d\n", players[A].shipPartsLeft, players[B].shipPartsLeft);
	}
	
}
char changeToBasicField(char field)
{
	if (field == '%' || field == '@' || field == '!')
		field = '+';

	return field;
}
Bool playerShipPlacementFeasible(Player* player, Ship* ship)
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
Bool onShip(Player* players, int y, int x)
{
	for(int p = 0; p <= 1; p++)
		for (int type = 0; type < TypesOfShips; type++)
		{
			for (int id = 0; id < players[p].maxShips[type]; id++)
			{
				switch (players[p].ships[type][id].direction)
				{
				case N:
					for (int i = 0; i < players[p].ships[type][id].length; i++)
						if (players[p].ships[type][id].y - i == y && players[p].ships[type][id].x == x)
						{
							return True;
						}
				}
			}
		}
	return False;
}

Bool shootShip(Board* board, Player* players, int y, int x)
{
	Ship pendingShip;

	for (int p = 0; p <= 1; p++)
		for (int type = 0; type < TypesOfShips; type++)
		{
			for (int id = 0; id < players[p].maxShips[type]; id++)
			{
				switch (players[p].ships[type][id].direction)
				{
				case N: // Facing Y-
					for (int i = 0; i < players[p].ships[type][id].length; i++)
						if ( (players[p].ships[type][id].y + i == y) && (players[p].ships[type][id].x == x) )
						{
							createShip(&pendingShip, static_cast<ShipType>(type), players[p].ships[type][id].y, players[p].ships[type][id].x, players[p].ships[type][id].direction, False, players[p].ships[type][id].part, players[p].ships[type][id].shipOnline);
							if (pendingShip.part[i] != PART_DESTROYED)
								players[p].shipPartsLeft -= 1;
							pendingShip.part[i] = PART_DESTROYED;
							updateShip(board, &players[p].ships[type][id], &pendingShip);
							players[p].ships[type][id] = pendingShip;
							return True;
						}
					break;
				case S: // Facing Y+
					for (int i = 0; i < players[p].ships[type][id].length; i++)
						if (players[p].ships[type][id].y = i == y && players[p].ships[type][id].x == x)
						{
							createShip(&pendingShip, static_cast<ShipType>(type), players[p].ships[type][id].y, players[p].ships[type][id].x, players[p].ships[type][id].direction, False, players[p].ships[type][id].part, players[p].ships[type][id].shipOnline);
							pendingShip.part[i] = PART_DESTROYED;
							updateShip(board, &players[p].ships[type][id], &pendingShip);
							players[p].ships[type][id] = pendingShip;
							return True;
						}
					break;
				case E: // Facing X+
					for (int i = 0; i < players[p].ships[type][id].length; i++)
						if (players[p].ships[type][id].y == y && players[p].ships[type][id].x - i == x)
						{
							createShip(&pendingShip, static_cast<ShipType>(type), players[p].ships[type][id].y, players[p].ships[type][id].x, players[p].ships[type][id].direction, False, players[p].ships[type][id].part, players[p].ships[type][id].shipOnline);
							pendingShip.part[i] = PART_DESTROYED;
							updateShip(board, &players[p].ships[type][id], &pendingShip);
							players[p].ships[type][id] = pendingShip;
							return True;
						}
					break;
				case W: // Facing X-
					for (int i = 0; i < players[p].ships[type][id].length; i++)
						if (players[p].ships[type][id].y == y && players[p].ships[type][id].x + i == x)
						{
							createShip(&pendingShip, static_cast<ShipType>(type), players[p].ships[type][id].y, players[p].ships[type][id].x, players[p].ships[type][id].direction, False, players[p].ships[type][id].part, players[p].ships[type][id].shipOnline);
							pendingShip.part[i] = PART_DESTROYED;
							updateShip(board, &players[p].ships[type][id], &pendingShip);
							players[p].ships[type][id] = pendingShip;
							return True;
						}
					break;
				default:
					return False;
				}
			}
		}
	return False;
}
void deleteShip(Board* board, Ship* ship)
{
	switch (ship->direction)
	{
	case N: //Facing Y-, draw in Y+
		for (int i = 0; i < ship->length; i++)
			board->fields[ship->y + i][ship->x] = FIELD_EMPTY;
		break;
	case S: //Facing Y+, draw in Y-
		for (int i = 0; i < ship->length; i++)
			board->fields[ship->y - i][ship->x] = FIELD_EMPTY;
		break;
	case E: //Facing X+, draw in X-
		for (int i = 0; i < ship->length; i++)
			board->fields[ship->y][ship->x - i] = FIELD_EMPTY;
		break;
	case W: //Facing X-, draw in X+
		for (int i = 0; i < ship->length; i++)
			board->fields[ship->y][ship->x + i] = FIELD_EMPTY;
		break;
	}
	ship->shipOnline = False;
}
void placeShip(Board* board, Ship* ship)
{
	if (checkShipPositionBoard(board, ship) == False)
		return;

	Field shipPart = FIELD_EMPTY;

	for (int i = 0; i < ship->length; i++)
	{
		shipPart = static_cast<Field>(ship->part[i]);
		switch (ship->direction)// Ships starts at head and extends bacwards
		{
		case N: //Facing Y-
				board->fields[ship->y + i][ship->x] = shipPart;
				break;
		case S: //Facing Y-
				board->fields[ship->y - i][ship->x] = shipPart;
				break;
		case E: //Facing X+
				board->fields[ship->y][ship->x - i] = shipPart;
				break;
		case W: //Facing X-
				board->fields[ship->y][ship->x + i] = shipPart;
				break;
		}
	}
	ship->shipOnline = False;
}
void updateShip(Board* board, Ship* oldShip, Ship* newShip)
{
	deleteShip(board, oldShip);
	placeShip(board, newShip);
}
void place1(Board* board, int y, int x, char piece) 
{
	board->fields[y][x] = piece;
}

Bool checkShipPositionBoard(Board* board, Ship* ship)
{
	Bool correctMove = True;
	if (ship->x < 0 || ship->x >= board->sizeX || ship->y < 0 || ship->y >= board->sizeY)
	{
		switch (ship->direction)
		{
		case N://Facing: Y-
			for (int i = 0; i < ship->length; i++) // check colision
			{
				if (board->fields[ship->y + i][ship->x] != FIELD_EMPTY)
				{
					correctMove = False;
					break;
				}
			}
			for (int i = -1; i < ship->length+1; i++) // check if touches other ships
			{
				if (
					board->fields[ship->y + i][ship->x-1] != FIELD_EMPTY ||
					board->fields[ship->y + i][ship->x-1] != FIELD_REEF  ||
					board->fields[ship->y + i][ship->x+1] != FIELD_EMPTY ||
					board->fields[ship->y + i][ship->x+1] != FIELD_REEF
					)

				{
					correctMove = False;
					break;
				}
			}
			break;

		case S: // FACING Y+
			for (int i = 0; i < ship->length; i++) // check colision
			{
				if (board->fields[ship->y - i][ship->x] != FIELD_EMPTY)
				{
					correctMove = False;
					break;
				}
			}
			for (int i = -1; i < ship->length + 1; i++) // check if touches other ships
			{
				if (
					board->fields[ship->y - i][ship->x - 1] != FIELD_EMPTY ||
					board->fields[ship->y - i][ship->x - 1] != FIELD_REEF ||
					board->fields[ship->y - i][ship->x + 1] != FIELD_EMPTY ||
					board->fields[ship->y - i][ship->x + 1] != FIELD_REEF
					)

				{
					correctMove = False;
					break;
				}
			}
			break;

		case E: // FACING X+
			for (int i = 0; i < ship->length; i++) // check colision
			{
				if (board->fields[ship->y][ship->x - i] != FIELD_EMPTY)
				{
					correctMove = False;
					break;
				}
			}
			for (int i = -1; i < ship->length + 1; i++) // check if touches other ships
			{
				if (
					board->fields[ship->y - 1][ship->x + i] != FIELD_EMPTY ||
					board->fields[ship->y - 1][ship->x + i] != FIELD_REEF ||
					board->fields[ship->y + 1][ship->x + i] != FIELD_EMPTY ||
					board->fields[ship->y + 1][ship->x + i] != FIELD_REEF
					)

				{
					correctMove = False;
					break;
				}
			}
			break;

		case W: // FACING X-
			for (int i = 0; i < ship->length; i++) // check colision
			{
				if (board->fields[ship->y][ship->x + i] != FIELD_EMPTY)
				{
					correctMove = False;
					break;
				}
			}
			for (int i = -1; i < ship->length + 1; i++) // check if touches other ships
			{
				if (
					board->fields[ship->y - 1][ship->x - i] != FIELD_EMPTY ||
					board->fields[ship->y - 1][ship->x - i] != FIELD_REEF  ||
					board->fields[ship->y + 1][ship->x - i] != FIELD_EMPTY ||
					board->fields[ship->y + 1][ship->x - i] != FIELD_REEF
					)

				{
					correctMove = False;
					break;
				}
			}
			break;
		}
	}
	if (correctMove)
		return True;

	return False;
}