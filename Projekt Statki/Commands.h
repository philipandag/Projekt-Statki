#pragma once
#include <stdlib.h>
#include "EnumsAndConst.h"
#include "OtherUseful.h"


const int CommandsAmount = 20;
const int MaxCommandLength = 20;
enum Command {
	ERROR,
	STATE, 
	PRINT,
	SET_FLEET,
	NEXT_PLAYER,
	PLAYERA,
	PLAYERB,
	PLACE_SHIP,
	SHOOT,

};




void commandsArgsInit();

Command recogniseCommand(const char* command);
