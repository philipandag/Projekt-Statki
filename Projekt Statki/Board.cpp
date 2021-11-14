#include "Board.h"


Board* createBoard(int y, int x)
{
	if (x > 0 && y > 0)
	{
		Board* board;
		board = (Board*)malloc(sizeof(Board));

		board->fields = (int**)malloc(sizeof(int*) * y);
		for (int i = 0; i < y; i++)
		{
			board->fields[i] = (int*)malloc(sizeof(int) * x);
			for (int j = 0; j < x; j++)
			{
				board->fields[i][j] = EMPTY;
			}
		}


		board->sizeY = y;
		board->sizeX = x;

		return board;
	}

}

void printBoard(Board* board)
{
	int xIndexLength = intLength(board->sizeX, baseX); 
	int yIndexLength = intLength(board->sizeY, baseY); 
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
					index = (x / power10(-y-1))%baseX + '0'; //Oddzielenie liczb dziesi¹tek od jednoœci
					printf(" %c", index);				
				}
			}
			else if (x < 0)
			{
				// Indeksy Y - z lewej
				char index;
				index = (y / power10(-x-1)) % baseY + '0';	
				printf("%c", index);
			}
			else
			{
				//Plansza w³aœciwa
				if( y < board->sizeY && x < board->sizeX)
					printf(" %c", board->fields[y][x]);
			}
			if (x == -1)
				printf(" ");
		}
		if (y == -1)
			printf("\n");
		printf("\n");
	}
}

void place1(Board* board, int y, int x, char piece) {
	if(y >= 0 && y < board->sizeY && x >= 0 && x < board->sizeX)
		board->fields[y][x] = piece;
}


int checkShipPositionBoard(Board* board, Ship* ship)
{
	Bool correctMove = True;
	if (ship->x < 0 || ship->x >= board->sizeX || ship->y < 0 || ship->y >= board->sizeY)
	{
		switch (ship->direction)
		{
		case N:
			for (int i = 0; i < ship->type; i++) // check colision
			{
				if (board->fields[ship->y + i][ship->x] != EMPTY)
				{
					correctMove = False;
					break;
				}
			}
			for (int i = -1; i < ship->type+1; i++) // check if touches other ships
			{
				if (!(
					board->fields[ship->y + i][ship->x-1] == EMPTY ||	
					board->fields[ship->y + i][ship->x-1] == REEF  ||	 
					board->fields[ship->y + i][ship->x+1] == EMPTY ||	
					board->fields[ship->y + i][ship->x+1] == REEF 
					))

				{
					correctMove = False;
					break;
				}
			}
			break;

		case S:
			for (int i = 0; i < ship->type; i++) // check colision
			{
				if (board->fields[ship->y - i][ship->x] != EMPTY)
				{
					correctMove = False;
					break;
				}
			}
			for (int i = -1; i < ship->type + 1; i++) // check if touches other ships
			{
				if (!(
					board->fields[ship->y - i][ship->x - 1] == EMPTY ||
					board->fields[ship->y - i][ship->x - 1] == REEF ||
					board->fields[ship->y - i][ship->x + 1] == EMPTY ||
					board->fields[ship->y - i][ship->x + 1] == REEF
					))

				{
					correctMove = False;
					break;
				}
			}
			break;

		case E:
			for (int i = 0; i < ship->type; i++) // check colision
			{
				if (board->fields[ship->y][ship->x + i] != EMPTY)
				{
					correctMove = False;
					break;
				}
			}
			for (int i = -1; i < ship->type + 1; i++) // check if touches other ships
			{
				if (!(
					board->fields[ship->y - 1][ship->x + i] == EMPTY ||
					board->fields[ship->y - 1][ship->x + i] == REEF ||
					board->fields[ship->y + 1][ship->x + i] == EMPTY ||
					board->fields[ship->y + 1][ship->x + i] == REEF
					))

				{
					correctMove = False;
					break;
				}
			}
			break;

		case W:
			for (int i = 0; i < ship->type; i++) // check colision
			{
				if (board->fields[ship->y][ship->x - i] != EMPTY)
				{
					correctMove = False;
					break;
				}
			}
			for (int i = -1; i < ship->type + 1; i++) // check if touches other ships
			{
				if (!(
					board->fields[ship->y - 1][ship->x - i] == EMPTY ||
					board->fields[ship->y - 1][ship->x - i] == REEF ||
					board->fields[ship->y + 1][ship->x - i] == EMPTY ||
					board->fields[ship->y + 1][ship->x - i] == REEF
					))

				{
					correctMove = False;
					break;
				}
			}
			break;
		}
	}
	if (correctMove)
		return 1;
	else
		return 0;
}