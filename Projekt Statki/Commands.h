#pragma once
#include "Board.h"

const int firstCommand = 1;
const int CommandsAmount = 10;
const int MaxCommandLength = 100;

enum Command 
{
	ERROR,
	STATE, 
	PRINT,
	SET_FLEET,
	NEXT_PLAYER,
	EXTENDED_SHIPS,
	PLAYERA,
	PLAYERB,
	PLACE_SHIP,
	SHOOT
};

enum CommandArea {

	COMMAND_NONE,
	COMMAND_STATE,
	COMMAND_PLAYERA,
	COMMAND_PLAYERB
};



void commandsArgsInit();

Command recogniseCommand(const char* command);

void executeCommand(Command id, Board* board, Player* players, PlayerId* currentPlayer, char* command);

void throwException(const char* command, const char* cause);