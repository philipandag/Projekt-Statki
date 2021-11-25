#include "mainFunctions.h"
int readInput(char* inputBuffer, int size)
{
	if (fgets(inputBuffer, size, stdin) == NULL)
		return -1;
	if (strlen(inputBuffer) > 1)
		return 1;
	return 0;
			
}
