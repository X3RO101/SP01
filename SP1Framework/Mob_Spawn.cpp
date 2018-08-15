#include"Mob_Spawn.h"

char** MapLocation()
{
	return 0;
}

char SetLocation(char ySet[4], char xSet[4])
{
	//srand()
	srand(time(nullptr));

	//random position
	char xPos = rand() % 87 + 1;
	char yPos = rand() % 15 + 1;

	//definition
	bool AvailabilityCheck;

	//set position
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			//assign position
			xSet[j] = xPos;
			ySet[i] = yPos;

		}

	}
	return xSet[4];
	return ySet[4];
}

bool LocationCheck(char(*CheckArray)[4][4])
{
	int Counter = 0;
	char* yLocation[4];
	char* xLocation[4];

	SetLocation(yLocation[4], xLocation[4]);

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			while (*xLocation[j] != ' ' && *yLocation[i] != ' ')
			{
				xLocation[j] += 2;
			}

		}
		Counter++;
	}

	if (Counter == 4)
	{
		return true;
	}

}