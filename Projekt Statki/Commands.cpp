#include "Commands.h"

const char* commandsText[CommandsAmount];
int commandArgs[CommandsAmount];

void commandsArgsInit()
{
	for (int i = 0; i < CommandsAmount; i++)
		commandsText[i] = (const char*)malloc(sizeof(const char*) * MaxCommandLength);
	
	// STATE COMMANDS
	commandArgs[STATE] = 0;
	commandsText[STATE] = "[state]";

	commandArgs[PRINT] = 1;
	commandsText[PRINT] = "PRINT";

	commandArgs[SET_FLEET] = 4;
	commandsText[SET_FLEET] = "SET_FLEET";

	commandArgs[NEXT_PLAYER] = 1;
	commandsText[NEXT_PLAYER] = "NEXT_PLAYER";



	//PLAYER COMMANDS
	commandArgs[PLAYERA] = 0;
	commandsText[PLAYERA] = "[playerA]";

	commandArgs[PLAYERB] = 0;
	commandsText[PLAYERB] = "[playerB]";

	commandArgs[PLACE_SHIP] = 5;
	commandsText[PLACE_SHIP] = "PLACE_SHIP";

	commandArgs[SHOOT] = 2;
	commandsText[SHOOT] = "SHOOT";
}

Command recogniseCommand(const char* command)
{
	Bool commands[20] = {False};
	int commandsLeft = CommandsAmount;
	for (int i = 0; command[i] != ' '; i++)
	{
		if (command[i] == '\0' || command[i] == '\n' || i > MaxCommandLength)
			return ERROR;
		for (int cID = 0; cID < commandsLeft; cID++)
		{
			if(commands[cID] == True)
			if (commandsText[cID][i] != command[i])
			{
				commands[cID] = False;
				commandsLeft--;
			}
		}
	}
	if (commandsLeft == 1)
		for (int i = 0; i < CommandsAmount; i++)
			if (commands[i] == True)
				return static_cast<Command>(i);
}