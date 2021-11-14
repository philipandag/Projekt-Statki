#define _CRT_SECURE_NO_WARNINGS

#include<cstdio>
#include<cstdlib>
#include "EnumsAndConst.h"
#include "OtherUseful.h"
#include "Board.h"
#include "Player.h"
#include "Ship.h"
#include "Commands.h"
using namespace std;


int main()
{
	Board* board;
	board = createBoard(SizeY, SizeX);

	Player player[2];
	player[A].ships = createShips(playerMaxCAR, playerMaxBAT, playerMaxCRU, playerMaxDES);
	player[B].ships = createShips(playerMaxCAR, playerMaxBAT, playerMaxCRU, playerMaxDES);
	int shipsAmount = 2 * (playerMaxCAR + playerMaxBAT + playerMaxCRU + playerMaxDES);

	Ship** ships = (Ship**)malloc(sizeof(Ship*) * shipsAmount);
	
	for (int j = 0; j < typesOfShips; j++)
		ships[j] = player[A].ships[j];

	for (int j = 0; j < typesOfShips; j++)
		ships[j + shipsAmount] = player[A].ships[j];

	PlayerId currentPlayer = A;

	Bool gameover = False;


	char userInput[MaxCommandLength];
	//############################### MAIN LOOP ##########################
	while (!gameover)
	{		
		printBoard(board);
		printf("COMMAND: ");
		scanf("%20s\n", userInput);
		printf("ITS: ");
		printf("%i", recogniseCommand(userInput));
		getchar();
	}
	return 0;
}