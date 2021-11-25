#define _CRT_SECURE_NO_WARNINGS

#include "main.h"

using namespace std;


int main()
{
	GameState* gameState = createGameState();
	PlayerId currentPlayer = A;
	PlayerId winner = BOTH;
	char* userInput = (char*)malloc(sizeof(char)*MaxCommandLength);
	Bool commandResult = True;
	Bool gameOver = False;

	gameState->board = createBoard(DefaultSizeY, DefaultSizeX);
	setStartingBoundary(gameState->players[A], 0, 0, 9, 10);
	setStartingBoundary(gameState->players[B], 10, 0, 20, 10);
	commandsArgsInit(gameState);

	//############################### MAIN LOOP ##########################
	while (!gameOver)
	{			
		switch (readInput(userInput, MaxCommandLength))
		{
		case 1:
			commandResult = executeCommand(recogniseCommand(userInput), gameState, userInput);
			break;
		case -1:
			gameOver = True;
			break;
		case 0:
			break;
		}

		if (commandResult == False)
			gameOver = True;

		winner = checkWin(gameState->players);
		
		if (winner != P_NONE)
		{
			printf("%c WON", (winner + 'A'));
			gameOver = True;
		}
	}

	free(gameState->board);
	free(gameState->players);
	free(gameState);
	return 0;
}