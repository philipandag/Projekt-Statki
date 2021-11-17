#define _CRT_SECURE_NO_WARNINGS

#include "Commands.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

using namespace std;

int main()
{
	Board* board = createBoard(SizeY, SizeX); 	

	Player player[2];
	createShips(&player[A]);
	createShips(&player[B]);
	setStartingBoundary(&player[A], 0, 0, 9, 10);
	setStartingBoundary(&player[B], 10, 0, 20, 10);
	player[A].shipPartsLeft = 0;
	player[B].shipPartsLeft = 0;

	Ship** ships = (Ship**)malloc(sizeof(Ship*) * TypesOfShips * 2);

	for (int j = 0; j < TypesOfShips; j++)
		ships[j] = player[A].ships[j];

	for (int j = 0; j < TypesOfShips; j++)
		ships[j + TypesOfShips] = player[B].ships[j];

	PlayerId currentPlayer = A;

	Bool gameover = False;

	commandsArgsInit();
	char userInput[MaxCommandLength];
	//############################### MAIN LOOP ##########################
	//printBoard(board);
	while (!gameover)
	{			
		//printf("COMMAND: ");
		//scanf("%20s", userInput);
		if (!fgets(userInput, sizeof(userInput), stdin))
			break;
		if(strlen(userInput)>1)
			executeCommand(recogniseCommand(userInput), board, player, &currentPlayer, userInput);
	}

	free(board);
	return 0;
}