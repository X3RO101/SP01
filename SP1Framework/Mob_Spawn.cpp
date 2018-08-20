#include"Mob_Spawn.h"
#include"game.h"


// set 4 random locations
char SetLocation(char ySet[4], char xSet[4])
{
	//srand()
	srand(time(nullptr));

	//random position
	int xPos = (rand() % 78 + 1) + (rand() % 10);
	int yPos = (rand() % 9 + 1) + (rand() % 6);

	//definition
	bool AvailabilityCheck = true;
	bool ReturnBool;

	LocationCheck(ReturnBool);

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
	if (ReturnBool == true)
	{
		AvailabilityCheck = true;
	}

	if (AvailabilityCheck == true)
	{
		return xSet[4];
		return ySet[4];

		//resets AvailabilityCheck
		if (AvailabilityCheck == true)
		{
			AvailabilityCheck = false;
		}
	}

}

//check if it's empty space
bool LocationCheck(bool ReturnChecking)
{
	string Map;
	int *Maze[15];
	int xMaze = 87;
	char *yLocation[4];
	char *xLocation[4];
	bool LevelComplete = false; // pass when level is complete
	int Counter = 0;
	int FinalCounter = 0;

	/*
	line 55 to 123 is similar to arraymaker function
	... similar

	*/
	//2D Array
	for (int i = 0; i < 86; i++)
	{
		Maze[i] = new int[xMaze];
	}
	string yAcross;
	string xAcross;
	string mapLoad;
	int y;
	int x;
	int Level = 0;

	//pass by value
	SetLocation(yLocation[4], xLocation[4]);

	if (Level == 0 && LevelComplete == false)
	{
		mapLoad += "lvl1.txt";

	}
	else if (Level == 0 && LevelComplete == true)
	{
		mapLoad += "lvl2.txt";
	}

	ifstream currentLevel;

	currentLevel.open(mapLoad);
	getline(currentLevel, xAcross);
	getline(currentLevel, yAcross);
	y = stoi(yAcross);
	x = stoi(xAcross);
	//==============================================================================================================================================
	//Load map
	//==============================================================================================================================================
	//for (int check = 0; check <3; check++) makes it loop such that it loops for 4 sets of location
	for (int laod = 0; laod < 3; laod++)
	{
		for (int i = 0; i < (y - 1); ++i)
		{
			string Row;
			char Char;
			getline(currentLevel, Row);
			for (int j = 0; j < (x - 1); ++j)
			{
				//in this loop, there's two things to do:
				// assign each array location a symbol
				// make sure that the location is "defined", such that the location is the one in the map
				Char = Row[j];
				switch (Char)
				{
				case'#':
					Maze[i][j] = 219; // wall

				case' ':
					Maze[i][j] = ' '; // empty space

				case'k':
					Maze[i][j] = 'k'; //key

				case 'o':
					Maze[i][j] = 'o'; //End Point

				case 'x':
					Maze[i][j] = 'X'; // Start Point
				}

			}
		}

		//checking
		//check if empty area is available
		for (int i = 0; i < sizeof(yAcross); i++)
		{
			for (int j = 0; i < sizeof(xAcross); j++)
			{
				int checkX = xAcross[j];
				int checkY = yAcross[i];

				//replace current i and j to become the coord
				j = checkX;
				i = checkY;

				while (Maze[i][j] != ' ')
				{
					checkX = rand() % 87 + 1;
					j = checkX;
				}

				if (Maze[i][j] == ' ')
				{
					Counter++;
				}

				while ((xAcross[i + 1] - xAcross[i]) < 3 || (xAcross[i] - xAcross[i + 1]) < 3)
				{
					xAcross[i] += 1;
				}
				if ((xAcross[i + 1] - xAcross[i]) > 3 || (xAcross[i] - xAcross[i + 1]) > 3)
				{
					FinalCounter++;
				}
			}
		}


	}

	if (Counter == FinalCounter == 4)
	{
		ReturnChecking = true;
		return ReturnChecking;
	}
}