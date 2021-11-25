#pragma once
//#include "CommandsFunctions.h"
#include "Board.h"


const int firstCommand = 1;
const int CommandsAmount = 20;
const int MaxCommandLength = 100;
const int MaxDifferentErrors = 10;
const int MaxErrorSize = 20;



enum Command {
	ERROR,

	STATE,
	PRINT,
	SET_FLEET,
	NEXT_PLAYER,
	EXTENDED_SHIPS,
	INIT_POSITION,
	SHIP,
	REEF,
	BOARD_SIZE,

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

struct GameState {
	Board* board;
	Player** players;
	PlayerId* currentPlayer;
	GameLogic* gameLogic;
	CommandArea* commandArea;

};


void commandsArgsInit(GameState* game);

GameState* createGameState();

void throwException(const char* command, const char* cause);




Command recogniseCommand(const char* command);

Bool executeCommand(Command id, GameState* game, char* command);

PlayerId checkWin(Player** players);

Bool commandSTATE(CommandArea area, GameState* game, char* command);

Bool commandPRINT(GameState* game, char* arg, char* command);

Bool commandSET_FLEET(GameState* game, char* arg, char* command);

Bool commandNEXT_PLAYER(GameState* game, char* arg, char* command);

Bool commandINIT_POSITION(GameState* game, char* arg, char* command);

Bool commandSHIP(GameState* game, char* arg, char* command);

Bool commandREEF(GameState* game, char* arg, char* command);

Bool commandBOARD_SIZE(GameState* game, char* arg, char* command);

Bool commandPLACE_SHIP(GameState* game, char* arg, char* command);

Bool commandSHOOT(GameState* game, char* arg, char* command);

Bool parseInput_player(char* p);

Bool parseInput_ship(char* c_shipType, ShipType* shipType);

Bool parseInput_direction(char c_direction, Compass* direction);

Bool parseInput_parts(char* cparts, ShipParts* parts, ShipType type);

Bool nextArg(char** command);

PlayerId commandAreaToPlayerId(CommandArea area);

PlayerId charToPlayerId(char c);

PlayerId nextPlayer(PlayerId id);

