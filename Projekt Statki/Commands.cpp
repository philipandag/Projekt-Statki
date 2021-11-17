#define _CRT_SECURE_NO_WARNINGS
#include "Commands.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

const char* commandsText[CommandsAmount];
int commandArgs[CommandsAmount];
Bool Initialised = False;
CommandArea commandArea;
GameLogic gameLogic;

const char* errorCause[CommandsAmount][10];


void commandsArgsInit()
{
	Initialised = True;
	gameLogic = BASIC_LOGIC;
	commandArea = COMMAND_NONE;
	for (int i = 0; i < CommandsAmount; i++)
		commandsText[i] = (const char*)malloc(sizeof(char) * MaxCommandLength);
	
	errorCause[ERROR][0] = "UNKNOWN COMMAND";

	// STATE COMMANDS
	commandArgs[STATE] = 0;
	commandsText[STATE] = "[state]";
	errorCause[STATE][0] = "STATE COMMAND ERROR";

	commandArgs[PRINT] = 1;
	commandsText[PRINT] = "PRINT";
	errorCause[PRINT][0] = "BASIC LOGIC - ONLY PRINT 0 ALLOWED";
	errorCause[PRINT][1] = "PRINT MODE SHOULD BE EITHER 0 OR 1";
	errorCause[PRINT][2] = "NO PLAYER SELECTED";

	commandArgs[SET_FLEET] = 4;
	commandsText[SET_FLEET] = "SET_FLEET";
	errorCause[SET_FLEET][0] = "FIELD DOES NOT EXIST";

	commandArgs[NEXT_PLAYER] = 1;
	commandsText[NEXT_PLAYER] = "NEXT_PLAYER";
	errorCause[NEXT_PLAYER][0] = "NO SUCH PLAYER, USE A OR B";

	commandArgs[EXTENDED_SHIPS] = 0;
	commandsText[EXTENDED_SHIPS] = "EXTENDED_SHIPS";
	errorCause[EXTENDED_SHIPS][0] = "";


	//PLAYER COMMANDS
	commandArgs[PLAYERA] = 0;
	commandsText[PLAYERA] = "[playerA]";
	errorCause[PLAYERA][0] = "THE OTHER PLAYER EXPECTED";
	errorCause[PLAYERA][1] = "NOT ALL SHIPS PLACED";

	commandArgs[PLAYERB] = 0;
	commandsText[PLAYERB] = "[playerB]";
	errorCause[PLAYERB][0] = "THE OTHER PLAYER EXPECTED";
	errorCause[PLAYERB][1] = "NOT ALL SHIPS PLACED";

	commandArgs[PLACE_SHIP] = 5;
	commandsText[PLACE_SHIP] = "PLACE_SHIP";
	errorCause[PLACE_SHIP][0] = "FIELD DOES NOT EXIST";
	errorCause[PLACE_SHIP][1] = "NOT IN STARTING POSITION";
	errorCause[PLACE_SHIP][2] = "SHIP ALREADY PRESENT";
	errorCause[PLACE_SHIP][3] = "ALL SHIPS OF THE CLASS ALREADY SET";
	errorCause[PLACE_SHIP][4] = "NO SUCH SHIP CLASS, ALLOWED: CAR, BAT, CRU, DES";
	errorCause[PLACE_SHIP][5] = "NO PLAYER SELECTED";
	errorCause[PLACE_SHIP][6] = "NO SUCH DIRECTION, ALLOWED: N, S, E, W";
	errorCause[PLACE_SHIP][7] = "ILLEGAL SHIP POSITION";


	commandArgs[SHOOT] = 2;
	commandsText[SHOOT] = "SHOOT";
	errorCause[SHOOT][0] = "THE OTHER PLAYER EXPECTED";
	errorCause[SHOOT][1] = "FIELD DOES NOT EXIST";
	errorCause[SHOOT][2] = "NOT ALL SHIPS PLACED";
}

Command recogniseCommand(const char* command)
{
	if (Initialised == False)
		commandsArgsInit();

	Bool commands[CommandsAmount];
	boolSet(commands, True, CommandsAmount);

	int commandsLeft = CommandsAmount;
	for (int cID = firstCommand; cID < CommandsAmount; cID++)
	{
		for (int i = 0; i < MaxCommandLength; i++)
		{
			if (command[i] == ' ' || command[i] == '\0' || command[i] == '\n')
				break;

			if (commands[cID] == True)
			{
				if (commandsText[cID][i] != command[i])
				{
					commands[cID] = False;
					commandsLeft--;
					break;
				}
			}
			if(commandsText[cID][i+1] == '\0' && commands[cID] == True) // Jeœli sprawdzono ca³y wzorzec i wci¹¿ siê zgadza, to musi byæ to
				return static_cast<Command>(cID);
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
char* nextArg(char* command)
{
	for (int i = 0; i < MaxCommandLength; i++)
		if (command[i] == ' ')
			return &command[i + 1];
	return NULL;
}


void executeCommand(Command id, Board* board, Player* players, PlayerId* currentPlayer, char* command)
{
	char* arg;
	for (int i = 0; i < MaxCommandLength; i++)
		if (command[i] == '\n')
		{
			command[i] = '\0';
			break;
		}

	arg = nextArg(command); // Skip command name and go to arguments

	int printMode;
	char next;
	int y, x, input_id;
	char direction_b;
	char shipType_b[4];
	ShipType shipType;
	Compass direction;
	Ship shipPending;

	switch (id)
	{
		//############   STATE COMMANDS   ###################
	case STATE:
		if (commandArea == COMMAND_NONE)
			commandArea = COMMAND_STATE;
		else if (commandArea == COMMAND_STATE)
			commandArea = COMMAND_NONE;
		break;
		//=====================================================
	case PRINT:

		if (sscanf(arg, "%d", &printMode) != 1)
		{
			throwException(command, errorCause[PRINT][1]);
			break;
		}

		if (gameLogic == BASIC_LOGIC)
		{
			if (commandArea == COMMAND_STATE || commandArea == COMMAND_PLAYERA || commandArea == COMMAND_PLAYERB)
			{

				//if (printMode != 0)
				if (printMode != 0 && printMode != 1)
				{
					throwException(command, errorCause[PRINT][0]);
				}
				else
				{
					printBoard(board, printMode, gameLogic, players, *currentPlayer);
				}
			}
			else
			{
				throwException(command, errorCause[PRINT][2]);
			}
		}
		else
		{
			if (printMode != 0 && printMode != 1)
			{
				throwException(command, errorCause[PRINT][1]);
			}
			else if (commandArea == COMMAND_STATE)
			{
				printBoard(board, printMode, gameLogic, players, BOTH);
			}
			else if (commandArea == PLAYERA)
			{
				printBoard(board, printMode, gameLogic, players, A);
			}
			else if (commandArea == PLAYERB)
			{
				printBoard(board, printMode, gameLogic, players, B);
			}
			else
			{
				throwException(command, errorCause[PRINT][2]);
			}
		}
		break;
		//=====================================================
	case SET_FLEET:
		break;
		//=====================================================
	case NEXT_PLAYER:
		sscanf(arg, "%c", &next);
		if (next == 'A')
			*currentPlayer = A;
		else if (next == 'B')
			*currentPlayer = B;
		else
			throwException(command, errorCause[NEXT_PLAYER][0]);
		break;
		//=====================================================
	case EXTENDED_SHIPS:
		gameLogic = EXTENDED_LOGIC;
		break;


		//############   PLAYER COMMANDS   ###################
	case PLAYERA:
		if (commandArea == COMMAND_NONE && *currentPlayer == A)
			commandArea = COMMAND_PLAYERA;
		else if (commandArea == COMMAND_PLAYERA)
		{
			commandArea = COMMAND_NONE;
			*currentPlayer = B;
		}
		else
			throwException(command, errorCause[PLAYERA][0]);
		break;
		//=====================================================
	case PLAYERB:
		if (commandArea == COMMAND_NONE && *currentPlayer == B)
			commandArea = COMMAND_PLAYERB;
		else if (commandArea == COMMAND_PLAYERB)
		{
			commandArea = COMMAND_NONE;
			*currentPlayer = A;
		}
		else
			throwException(command, errorCause[PLAYERB][0]);
		break;
		//=====================================================
	case PLACE_SHIP:
		

		sscanf(arg, "%d", &y);
		arg = nextArg(arg);
		sscanf(arg, "%d", &x);
		arg = nextArg(arg);
		sscanf(arg, "%c", &direction_b);
		arg = nextArg(arg);
		sscanf(arg, "%d", &input_id);
		arg = nextArg(arg);
		sscanf(arg, "%3s", &shipType_b);
		arg = nextArg(arg);


		if (strcmp(shipType_b, "CAR") == 0)
			shipType = CAR;
		else if (strcmp(shipType_b, "BAT") == 0)
			shipType = BAT;
		else if (strcmp(shipType_b, "CRU") == 0)
			shipType = CRU;
		else if (strcmp(shipType_b, "DES") == 0)
			shipType = DES;
		else
		{
			throwException(command, errorCause[PLACE_SHIP][4]); // ShipType CHECKED
			break;
		}

		if (direction_b == 'N')
			direction = N;
		else if (direction_b == 'S')
			direction = S;
		else if (direction_b == 'E')
			direction = E;
		else if (direction_b == 'W')
			direction = W;
		else
		{
			throwException(command, errorCause[PLACE_SHIP][6]);	// Direction CHECKED
			break;
		}
		if (commandArea != COMMAND_PLAYERA && commandArea != COMMAND_PLAYERB)
		{
			throwException(command, errorCause[PLACE_SHIP][5]);	// If within player turn CHECKED
			break;
		}
		if (input_id >= players[*currentPlayer].maxShips[shipType])
		{
			throwException(command, errorCause[PLACE_SHIP][3]);	// ShipId CHECKED
			break;
		}
		if (players[*currentPlayer].ships[shipType][input_id].shipOnline == True)
		{
			throwException(command, errorCause[PLACE_SHIP][2]);	// If Ship placeable CHECKED
			break;
		}	

		createShip(&shipPending, shipType, y, x, direction, True, NULL, True);

		if (playerShipPlacementFeasible(&players[*currentPlayer], &shipPending) == False)
		{
			throwException(command, errorCause[PLACE_SHIP][1]);	// Last Check - colisions
			break;
		}

		if (checkShipPositionBoard(board, &shipPending) == False)
		{
			throwException(command, errorCause[PLACE_SHIP][7]);	// Last Check - colisions
			break;
		}
		
		players[*currentPlayer].ships[shipType][input_id] = shipPending;
		players[*currentPlayer].shipPartsLeft += ShipLength[shipType];
		placeShip(board, &shipPending);
		break;
		


		//=====================================================
	case SHOOT:
		sscanf(arg, "%d", &y);
		arg = nextArg(arg);
		sscanf(arg, "%d", &x);

		if ((commandArea == COMMAND_PLAYERA && *currentPlayer == A) || (commandArea == COMMAND_PLAYERB && *currentPlayer == B))
		{
			if (onBoard(board, y, x))
			{
				switch (gameLogic)
				{
				case BASIC_LOGIC:
					shootShip(board, players, y, x);
					break;
				case EXTENDED_LOGIC:
					break;
				case ADVANCED_LOGIC:
					break;
				}
				break;
			}
			else
				throwException(command, errorCause[SHOOT][1]);
			
		}
		else
		{
			throwException(command, errorCause[SHOOT][0]);
		}
		
		//=====================================================
	default:
		throwException(command, errorCause[ERROR][0]);
		break;
	}
}

void throwException(const char* command, const char* cause) 
{
	printf("INVALID OPERATION \"%s\": %s\n", command, cause);
}