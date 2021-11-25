#define _CRT_SECURE_NO_WARNINGS
#include "Commands.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

const char* CommandsText[CommandsAmount];
int CommandArgs[CommandsAmount];
const char* ErrorCause[CommandsAmount][10];

GameState* createGameState()
{
	GameState* game = (GameState*)malloc(sizeof(GameState));
	game->board = (Board*)malloc(sizeof(Board));

	game->players = (Player**)malloc(sizeof(Player*) * 2);
	game->players[A] = createPlayer();
	game->players[B] = createPlayer();

	game->currentPlayer = (PlayerId*)malloc(sizeof(PlayerId));
	*game->currentPlayer = A;

	game->gameLogic = (GameLogic*)malloc(sizeof(GameLogic));
	*game->gameLogic = BASIC_LOGIC;

	game->commandArea = (CommandArea*)malloc(sizeof(CommandArea));
	*game->commandArea = COMMAND_NONE;

	return game;
}

void commandsArgsInit(GameState* game)
{

	/*CommandsText = (const char**)malloc(sizeof(char*) * CommandsAmount);
	for (int i = 0; i < CommandsAmount; i++)
		CommandsText[i] = (char*)malloc(sizeof(char) * MaxCommandLength);

	CommandArgs = (int*)malloc(sizeof(int) * CommandsAmount);

	ErrorCause = (const char***)malloc(sizeof(const char**) * CommandsAmount);
	for (int i = 0; i < CommandsAmount; i++) {
		ErrorCause[i] = (const char**)malloc(sizeof(char*) * MaxDifferentErrors);
		for (int j = 0; j < MaxDifferentErrors; j++)
			ErrorCause[i][j] = (char*)malloc(sizeof(char) * MaxErrorSize);
	}

	
	for (int i = 0; i < CommandsAmount; i++)
		CommandsText[i] = (char*)malloc(sizeof(char) * MaxCommandLength);*/

	*game->gameLogic = BASIC_LOGIC;
	*game->commandArea = COMMAND_NONE;
	ErrorCause[ERROR][0] = "UNKNOWN COMMAND";
	ErrorCause[ERROR][1] = "WRONG ARGUMENTS";

	// STATE COMMANDS
	CommandArgs[STATE] = 0;
	CommandsText[STATE] = "[state]";
	ErrorCause[STATE][0] = "STATE COMMAND ERROR";

	CommandArgs[PRINT] = 1;
	CommandsText[PRINT] = "PRINT";
	ErrorCause[PRINT][0] = "BASIC LOGIC - ONLY PRINT 0 ALLOWED";
	ErrorCause[PRINT][1] = "PRINT MODE SHOULD BE EITHER 0 OR 1";
	ErrorCause[PRINT][2] = "NO PLAYER SELECTED";

	CommandArgs[SET_FLEET] = 4;
	CommandsText[SET_FLEET] = "SET_FLEET";
	ErrorCause[SET_FLEET][0] = "SHIPS AMOUNT MUST BE BETWEEN 0 AND 10";
	ErrorCause[SET_FLEET][1] = "ONLY AVAILABLE IN STATE";
	ErrorCause[SET_FLEET][2] = "NO SUCH PLAYER, USE A OR B";

	CommandArgs[NEXT_PLAYER] = 1;
	CommandsText[NEXT_PLAYER] = "NEXT_PLAYER";
	ErrorCause[NEXT_PLAYER][0] = "NO SUCH PLAYER, USE A OR B";

	CommandArgs[EXTENDED_SHIPS] = 0;
	CommandsText[EXTENDED_SHIPS] = "EXTENDED_SHIPS";
	ErrorCause[EXTENDED_SHIPS][0] = "";

	CommandArgs[INIT_POSITION] = 5;
	CommandsText[INIT_POSITION] = "INIT_POSITION";
	ErrorCause[INIT_POSITION][0] = "INIT_POSITION ERR";

	CommandArgs[SHIP] = 7;
	CommandsText[SHIP] = "SHIP";
	ErrorCause[SHIP][0] = "NO SUCH PLAYER, USE A OR B";
	ErrorCause[SHIP][1] = "NO SUCH SHIP CLASS, ALLOWED: CAR, BAT, CRU, DES";
	ErrorCause[SHIP][2] = "NO SUCH DIRECTION, ALLOWED: N, S, E, W";
	ErrorCause[SHIP][4] = "WRONG PARTS";
	ErrorCause[SHIP][5] = "SHIP ALREADY PRESENT";
	ErrorCause[SHIP][6] = "ALL SHIPS OF THE CLASS ALREADY SET";
	ErrorCause[SHIP][7] = "PLACING SHIP TOO CLOSE TO OTHER SHIP";
	ErrorCause[SHIP][8] = "PLACING SHIP ON REEF";
	ErrorCause[SHIP][3] = "ONLY AVAILABLE IN STATE";

	CommandArgs[REEF] = 2;
	CommandsText[REEF] = "REEF";
	ErrorCause[REEF][0] = "FIELD DOES NOT EXIST";

	CommandArgs[BOARD_SIZE] = 2;
	CommandsText[BOARD_SIZE] = "BOARD_SIZE";
	ErrorCause[BOARD_SIZE][0] = "BOARD_SIZE error";

	//PLAYER COMMANDS
	CommandArgs[PLAYERA] = 0;
	CommandsText[PLAYERA] = "[playerA]";
	ErrorCause[PLAYERA][0] = "THE OTHER PLAYER EXPECTED";
	ErrorCause[PLAYERA][1] = "NOT ALL SHIPS PLACED";

	CommandArgs[PLAYERB] = 0;
	CommandsText[PLAYERB] = "[playerB]";
	ErrorCause[PLAYERB][0] = "THE OTHER PLAYER EXPECTED";
	ErrorCause[PLAYERB][1] = "NOT ALL SHIPS PLACED";

	CommandArgs[PLACE_SHIP] = 5;
	CommandsText[PLACE_SHIP] = "PLACE_SHIP";
	ErrorCause[PLACE_SHIP][0] = "FIELD DOES NOT EXIST";
	ErrorCause[PLACE_SHIP][1] = "NOT IN STARTING POSITION";
	ErrorCause[PLACE_SHIP][2] = "SHIP ALREADY PRESENT";
	ErrorCause[PLACE_SHIP][3] = "ALL SHIPS OF THE CLASS ALREADY SET";
	ErrorCause[PLACE_SHIP][4] = "NO SUCH SHIP CLASS, ALLOWED: CAR, BAT, CRU, DES";
	ErrorCause[PLACE_SHIP][5] = "NO PLAYER SELECTED";
	ErrorCause[PLACE_SHIP][6] = "NO SUCH DIRECTION, ALLOWED: N, S, E, W";
	ErrorCause[PLACE_SHIP][7] = "PLACING SHIP TOO CLOSE TO OTHER SHIP";
	ErrorCause[PLACE_SHIP][8] = "PLACING SHIP ON REEF";


	CommandArgs[SHOOT] = 2;
	CommandsText[SHOOT] = "SHOOT";
	ErrorCause[SHOOT][0] = "THE OTHER PLAYER EXPECTED";
	ErrorCause[SHOOT][1] = "FIELD DOES NOT EXIST";
	ErrorCause[SHOOT][2] = "NOT ALL SHIPS PLACED";
	ErrorCause[SHOOT][3] = "NOT ALLOWED IN EXTENDED SHIPS";
	ErrorCause[SHOOT][4] = "CAN'T SHOOT MORE THAN ONCE A TURN";

	CommandArgs[MOVE] = 3;
	CommandsText[MOVE] = "MOVE";
	ErrorCause[MOVE][0] = "MOVE_SHIP ERROR";
	ErrorCause[MOVE][1] = "PLACING SHIP TOO CLOSE TO OTHER SHIP";
	ErrorCause[MOVE][2] = "PLACING SHIP ON REEF";
	ErrorCause[MOVE][3] = "SHIP WENT FROM BOARD";
	ErrorCause[MOVE][4] = "SHIP MOVED ALREADY";
	ErrorCause[MOVE][5] = "SHIP CANNOT MOVE";
}


Command recogniseCommand(const char* command)
{
	Bool commands[CommandsAmount];
	boolSet(commands, True, CommandsAmount);

	int commandsLeft = CommandsAmount;
	for (int cID = firstCommand; cID < CommandsAmount; cID++) {
		if(CommandsText[cID] != NULL)
			for (int i = 0; i < MaxCommandLength; i++)
			{
				if (command[i] == ' ' || command[i] == '\0' || command[i] == '\n')
					commands[cID] = False;

				if (commands[cID] == True) {

					if (CommandsText[cID][i] != command[i])
					{
						commands[cID] = False;
						commandsLeft--;
						break;
					}
				}
				if (CommandsText[cID][i + 1] == '\0' && commands[cID] == True) { // Jeœli sprawdzono ca³y wzorzec i wci¹¿ siê zgadza, to musi byæ to
					return static_cast<Command>(cID);
				}
			}
	}

	if (commandsLeft == 1)
	{
		for (int cID = 0; cID < CommandsAmount; cID++)
			if (commands[cID] == 1)
			{
				return static_cast<Command>(cID);
			}
	}

	return ERROR;
}

Bool nextArg(char** command)
{
	for (int i = 0; i < MaxCommandLength; i++)
	{
		if ((*command)[i] == ' ')
		{
			if ((*command)[i + 1] != ' ' && (*command)[i + 1] != '\0')
			{
				(*command) = &(*command)[i + 1];
				return True;
			}
			else
			{
				return False;
			}
		}
	}
	return False;
}

Bool executeCommand(Command id, GameState* game, char* command)
{
	char* arg = command;
	nextArg(&arg);
	for (int i = 0; i < MaxCommandLength; i++)
		if (command[i] == '\n')
		{
			command[i] = '\0';
			break;
		}


	int printMode;
	char p;
	int y, x, input_id, y2, x2;
	char c_direction;
	char c_shipType[4];
	char cparts[6];
	ShipParts parts[6];
	ShipType shipType;
	Compass direction;
	Ship shipPending;
	int car, bat, cru, des;

	switch (id)
	{
		//############   STATE COMMANDS   ###################
	case STATE:
		if ( !commandSTATE(COMMAND_STATE, game, command))
			return False;
		break;
	case PRINT:
		if ( !commandPRINT(game, arg, command))
			return False;
		break;
	case SET_FLEET:
		if ( !commandSET_FLEET(game, arg, command))
			return False;
		break;
	case NEXT_PLAYER:
		if ( !commandNEXT_PLAYER(game, arg, command))
			return False;
		break;
	case EXTENDED_SHIPS:
		*game->gameLogic = EXTENDED_LOGIC;
		break;
	case INIT_POSITION:
		if ( !commandINIT_POSITION(game, arg, command))
			return False;
		break;
	case SHIP:
		if ( !commandSHIP(game, arg, command))
			return False;
		break;
	case REEF:
		if ( !commandREEF(game, arg, command))
			return False;
		break;
	case BOARD_SIZE:
		if ( !commandBOARD_SIZE(game, arg, command))
			return False;
		break;
		//############   PLAYER COMMANDS   ###################
	case PLAYERA:
		if ( !commandSTATE(COMMAND_PLAYERA, game, command))
			return False;
		break;
	case PLAYERB:
		if ( !commandSTATE(COMMAND_PLAYERB, game, command))
			return False;
		break;
	case PLACE_SHIP:
		if ( !commandPLACE_SHIP(game, arg, command))
			return False;
		break;
	case SHOOT:
		if ( !commandSHOOT(game, arg, command))
			return False;
		break;
	case MOVE:
		if ( !commandMOVE(game, arg, command))
			return False;
		break;
		//=====================================================
	default:
		throwException(command, ErrorCause[ERROR][0]);
		return False;
		break;
	}
	return True;
}

void throwException(const char* command, const char* cause) 
{
	printf("INVALID OPERATION \"%s\": %s\n", command, cause);
}

PlayerId checkWin(Player** players)
{
	if (players[A]->allPlaced == True && players[A]->shipPartsLeft <= 0)
		return B;
	if (players[B]->allPlaced == True && players[B]->shipPartsLeft <= 0)
		return A;

	return P_NONE;
}

Bool parseInput_player(char* p)
{
	if (*p == 'A')
	{
		*p = A;
		return True;
	}
	else if (*p == 'B')
	{
		*p = B;
		return True;
	}
	return False;
}

Bool parseInput_ship(char* c_shipType, ShipType* shipType)
{
	if (strcmp(c_shipType, "CAR") == 0)
		*shipType = CAR;
	else if (strcmp(c_shipType, "BAT") == 0)
		*shipType = BAT;
	else if (strcmp(c_shipType, "CRU") == 0)
		*shipType = CRU;
	else if (strcmp(c_shipType, "DES") == 0)
		*shipType = DES;
	else
		return False;
	return True;
}

Bool parseInput_direction(char c_direction, Compass* direction)
{
	if (c_direction == 'N')
		*direction = N;
	else if (c_direction == 'S')
		*direction = S;
	else if (c_direction == 'E')
		*direction = E;
	else if (c_direction == 'W')
		*direction = W;
	else
		return False;
	return True;
}

Bool parseInput_parts(char* cparts, ShipParts* parts, ShipType type)
{
	for (int i = 0; i < ShipLength[type]; i++)
	{
		if (cparts[i] != '0' && cparts[i] != '1')
		{
			return False;
		}
		if (cparts[i] == '1')
		{
			if (i == 0)
				parts[i] = PART_RADAR;
			else if (i == ShipLength[type] - 1)
				parts[i] = PART_ENGINE;
			else if (i == 1)
				parts[i] = PART_CANNON;
			else
				parts[i] = PART_SHIP;
		}
		else
			parts[i] = PART_DESTROYED;
	}
	return True;
}

PlayerId commandAreaToPlayerId(CommandArea area)
{
	switch (area)
	{
	case COMMAND_PLAYERA:
		return A;
	case COMMAND_PLAYERB:
		return B;
	case COMMAND_STATE:
		return P_STATE;
	}
	return P_NONE;
}


PlayerId charToPlayerId(char c)
{
	return (PlayerId)(c - 'A');
}
PlayerId nextPlayer(PlayerId id)
{
	return (PlayerId)((int)(id + 1) % 2);
}

Bool commandSTATE(CommandArea area, GameState* game, char* command)
{
	PlayerId givenPlayer = commandAreaToPlayerId(area);
	switch (area)
	{
	case COMMAND_STATE:
		if (*game->commandArea == COMMAND_NONE) {
			*game->commandArea = COMMAND_STATE;
		}
		else if (*game->commandArea == COMMAND_STATE) {
			*game->commandArea = COMMAND_NONE;
		}
		else
		{
			throwException(command, ErrorCause[STATE][0]);
			return False;
		}
		break;
	case COMMAND_PLAYERA:
	case COMMAND_PLAYERB:
		if (*game->commandArea == COMMAND_NONE && *game->currentPlayer == givenPlayer)
		{
			Player* currentPlayer = game->players[*game->currentPlayer];
			*game->commandArea = area;
			currentPlayer->canShoot = True;
			for (int type = 0; type < TypesOfShips; type++)
				for (int id = 0; id < currentPlayer->maxShips[type]; id++)
					currentPlayer->ships[type][id].moves = 0;
		}
		else if (*game->commandArea == area)
		{
			*game->commandArea = COMMAND_NONE;
			*game->currentPlayer = nextPlayer(*game->currentPlayer);
		}
		else
		{
			throwException(command, ErrorCause[PLAYERA][0]);
			return False;
		}

		break;
	}
	return True;
}
Bool commandPRINT(GameState* game, char* arg, char* command)
{
	int printMode;
	if (sscanf(arg, "%d", &printMode) != 1 || printMode != 0 && printMode != 1)
	{
		throwException(command, ErrorCause[PRINT][1]);
		return False;
	}
	if (*game->commandArea != COMMAND_STATE && *game->commandArea != COMMAND_PLAYERA && *game->commandArea != COMMAND_PLAYERB)
	{
		throwException(command, ErrorCause[PRINT][2]);
		return False;
	}
	printBoard(game->board, printMode, *game->gameLogic, game->players, commandAreaToPlayerId(*game->commandArea));
	return True;
}

Bool commandSET_FLEET(GameState* game, char* arg, char* command)
{
	char p;
	int car, bat, cru, des;
	if (sscanf(arg, "%c %i %i %i %i", &p, &car, &bat, &cru, &des) != 5)
	{
		throwException(command, ErrorCause[ERROR][1]);
		return False;
	}
	if (parseInput_player(&p) == False) {
		throwException(command, ErrorCause[ERROR][1]);
		return False;
	}
	if (*game->commandArea != STATE)
	{
		throwException(command, ErrorCause[SET_FLEET][1]);
		return False;
	}
	if (setFleet(game->players[p], car, bat, cru, des) == False)
	{
		throwException(command, ErrorCause[SET_FLEET][0]);
		return False;
	}
	return True;
}

Bool commandNEXT_PLAYER(GameState* game, char* arg, char* command)
{
	char p;
	if (sscanf(arg, "%c", &p) == 1)
		if (parseInput_player(&p)) {
			*game->currentPlayer = (PlayerId)p;
		}
		else
		{
			throwException(command, ErrorCause[NEXT_PLAYER][0]);
			return False;
		}

	return True;
}

Bool commandINIT_POSITION(GameState* game, char* arg, char* command)
{
	char p;
	int y1, x1, y2, x2;
	if (sscanf(arg, "%c %d %d %d %d", &p, &y1, &x1, &y2, &x2) != 5)
	{
		throwException(command, ErrorCause[ERROR][1]);
		return False;
	}
	if (onBoard(game->board, y1, x1) && onBoard(game->board, y2, x2))
	{
		if (parseInput_player(&p) == False)
		{
			throwException(command, ErrorCause[ERROR][1]);
			return False;
		}
		setStartingBoundary(game->players[p], y1, x1, y2, x2);
	}
	return True;
}

Bool commandSHIP(GameState* game, char* arg, char* command)
{
	char p, c_direction, c_shipType[4], cparts[6];
	int x, y, input_id;
	ShipType shipType;
	Compass direction;
	ShipParts parts[5];
	Ship shipPending;

	if (sscanf(arg, "%c %d %d %c %d %3s %5s", &p, &y, &x, &c_direction, &input_id, &c_shipType, cparts) != 7)
	{
		throwException(command, ErrorCause[ERROR][1]);
		return False;
	}
	if (parseInput_player(&p) == False)
	{
		throwException(command, ErrorCause[SHIP][0]);
		return False;
	}
	if (parseInput_ship(c_shipType, &shipType) == False)
	{
		throwException(command, ErrorCause[SHIP][1]); // ShipType CHECK
		return False;
	}
	if (parseInput_direction(c_direction, &direction) == False)
	{
		throwException(command, ErrorCause[SHIP][2]);	// Direction CHECK
		return False;
	}
	if (parseInput_parts(cparts, parts, shipType) == False)
	{
		throwException(command, ErrorCause[SHIP][4]);
		return False;
	}
	if (*game->commandArea != COMMAND_STATE)
	{
		throwException(command, ErrorCause[SHIP][4]);
		return False;
	}
	if (game->players[p]->ships[shipType][input_id].shipOnline == True)
	{
		throwException(command, ErrorCause[SHIP][5]);	// If Ship placeable CHECK
		return False;
	}
	if (input_id >= game->players[p]->maxShips[shipType])
	{
		throwException(command, ErrorCause[SHIP][6]);	// ShipId CHECK
		return False;
	}

	createShip(&shipPending, shipType, y, x, direction, False, parts, True, True);
	if (!isShipInPlayersStartingPosition(game->players[p], &shipPending))
	{
		throwException(command, ErrorCause[SHIP][8]);	// ShipId CHECK
		return False;
	}
	Field collides = checkShipPositionBoard(game->board, &shipPending);
		switch (collides)
		{
		case FIELD_REEF:
			throwException(command, ErrorCause[SHIP][8]);	
			return False;
			break;
		case FIELD_SHIP:
		case FIELD_ENGINE:
		case FIELD_CANNON:
		case FIELD_RADAR:
			throwException(command, ErrorCause[SHIP][7]);	
			return False;
			break;
		case FIELD_EMPTY:
			break;
		default:
			throwException(command, ErrorCause[ERROR][0]);
		}

	game->players[p]->ships[shipType][input_id] = shipPending;
	game->players[p]->shipPartsLeft = countShipParts(game->players[p]);
	game->players[p]->allPlaced = allShipsPlaced(game->players[p]);
	placeShip(game->board, &shipPending);
	return True;
}

Bool commandREEF(GameState* game, char* arg, char* command)
{
	int y, x;
	if (sscanf(arg, "%d %d", &y, &x) != CommandArgs[REEF])
	{
		throwException(command, ErrorCause[ERROR][0]);
		return False;
	}
	if (!onBoard(game->board, y, x))
	{
		throwException(command, ErrorCause[REEF][0]);
		return False;
	}
	setBoardField(game->board, y, x, FIELD_REEF);
	return True;
}

Bool commandPLACE_SHIP(GameState* game, char* arg, char* command)
{
	int y, x, input_id;
	char c_direction, c_shipType[4];
	ShipType shipType;
	Compass direction;
	Ship shipPending;
	if (sscanf(arg, "%d %d %c %d %3s", &y, &x, &c_direction, &input_id, &c_shipType) != CommandArgs[PLACE_SHIP])
	{
		throwException(command, ErrorCause[ERROR][1]);
		return False;
	}
	if (parseInput_ship(c_shipType, &shipType) == False)
	{
		throwException(command, ErrorCause[PLACE_SHIP][4]); // ShipType CHECK
		return False;
	}
	if (game->players[*game->currentPlayer]->ships[shipType][input_id].shipOnline == True)
	{
		throwException(command, ErrorCause[PLACE_SHIP][2]);	// If Ship placeable CHECK
		return False;
	}
	if (input_id >= game->players[*game->currentPlayer]->maxShips[shipType])
	{
		throwException(command, ErrorCause[PLACE_SHIP][3]);	// ShipId CHECK
		return False;
	}
	if (*game->commandArea != COMMAND_PLAYERA && *game->commandArea != COMMAND_PLAYERB)
	{
		throwException(command, ErrorCause[PLACE_SHIP][5]);	// If within player turn CHECK
		return False;
	}
	if (parseInput_direction(c_direction, &direction) == False)
	{
		throwException(command, ErrorCause[PLACE_SHIP][6]);	// Direction CHECK
		return False;
	}

createShip(&shipPending, shipType, y, x, direction, True, NULL, True, True);
if (!isShipInPlayersStartingPosition(game->players[*game->currentPlayer], &shipPending))
{
	throwException(command, ErrorCause[PLACE_SHIP][1]);	// Last Check - colisions
	return False;
}

Field collides = checkShipPositionBoard(game->board, &shipPending);
switch (collides)
{
case FIELD_REEF:
	throwException(command, ErrorCause[PLACE_SHIP][8]);
	return False;
	break;
case FIELD_SHIP:
case FIELD_ENGINE:
case FIELD_CANNON:
case FIELD_RADAR:
	throwException(command, ErrorCause[PLACE_SHIP][7]);
	return False;
	break;
case FIELD_EMPTY:
	break;
default:
	throwException(command, ErrorCause[ERROR][0]);
}

game->players[*game->currentPlayer]->ships[shipType][input_id] = shipPending;
game->players[*game->currentPlayer]->shipPartsLeft += ShipLength[shipType];
game->players[*game->currentPlayer]->allPlaced = allShipsPlaced(game->players[*game->currentPlayer]);
placeShip(game->board, &shipPending);
return True;
}

Bool commandSHOOT(GameState* game, char* arg, char* command)
{
	int y, x;
	if (sscanf(arg, "%d %d", &y, &x) != CommandArgs[SHOOT])
	{
		throwException(command, ErrorCause[ERROR][1]);
		return False;
	}
	if (!(*game->commandArea == COMMAND_PLAYERA && *game->currentPlayer == A) && !(*game->commandArea == COMMAND_PLAYERB && *game->currentPlayer == B))
	{
		throwException(command, ErrorCause[SHOOT][0]);
		return False;
	}
	if (onBoard(game->board, y, x) == False)
	{
		throwException(command, ErrorCause[SHOOT][1]);
		return False;
	}
	if (allShipsPlaced(game->players[A]) == False || allShipsPlaced(game->players[B]) == False)
	{
		throwException(command, ErrorCause[SHOOT][2]);
		return False;
	}

	switch (*game->gameLogic)
	{
	case BASIC_LOGIC:
		if (game->players[*game->currentPlayer]->canShoot == True)
		{
			shootShip(game->board, game->players, y, x);
			//game->players[A]->shipPartsLeft = countShipParts(game->players[A]);
			//game->players[B]->shipPartsLeft = countShipParts(game->players[B]);
			game->players[*game->currentPlayer]->canShoot = False;
		}
		else
		{
			throwException(command, ErrorCause[SHOOT][4]);
			return False;
		}
		break;

	case EXTENDED_LOGIC:
		throwException(command, ErrorCause[SHOOT][3]);
		return False;
		break;

	case ADVANCED_LOGIC:
		break;
	}
	return True;
}

Bool commandBOARD_SIZE(GameState* game, char* arg, char* command)
{
	int y, x;
	if (sscanf(arg, "%d %d", &y, &x) != CommandArgs[BOARD_SIZE])
		return False;

	for (int i = 0; i < game->board->sizeY; i++)
		free(game->board->fields[i]);
	free(game->board->fields);
	free(game->board);
	game->board = createBoard(y, x);
	return True;
}

Bool commandMOVE(GameState* game, char* arg, char* command)
{
	int shipId;
	char c_shipType[4], moveDir;
	ShipType shipType;
	Player* currentPlayer = game->players[*game->currentPlayer];
	if (sscanf(arg, "%d %s %c", &shipId, &c_shipType, &moveDir) != CommandArgs[MOVE])
	{
		throwException(command, ErrorCause[ERROR][1]);
		return False;
	}

	if (!parseInput_ship(c_shipType, &shipType))
	{
		throwException(command, ErrorCause[ERROR][1]);
		return False;
	}
	if (moveDir != 'F' && moveDir != 'L' && moveDir != 'R')
	{
		throwException(command, ErrorCause[ERROR][1]);
		return False;
	}
	Ship* currentShip = &currentPlayer->ships[shipType][shipId];

	if(currentShip->moves >= 3)
	{
		throwException(command, ErrorCause[MOVE][4]);
		return False;
	}
	if (currentShip->part[currentShip->length-1] == PART_DESTROYED)
	{
		throwException(command, ErrorCause[MOVE][4]);
		return False;
	}
	switch (rotateShip(game->board, &currentPlayer->ships[shipType][shipId], moveDir))
	{
	case FIELD_EMPTY:
		currentShip->moves += 1;
		return True;
		break;
	case FIELD_SHIP:
	case FIELD_ENGINE:
	case FIELD_CANNON:
	case FIELD_RADAR:
		throwException(command, ErrorCause[MOVE][1]);
		return False;
		break;
	case FIELD_REEF:
		throwException(command, ErrorCause[MOVE][2]);
		return False;
		break;
	case FIELD_OUT_OF_BOARD:
		throwException(command, ErrorCause[MOVE][3]);
		return False;
		break;
	}

	
	return True;
}





