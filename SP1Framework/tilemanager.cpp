#include "tilemanager.h"

char **map;

void arraymaker(string levelgen())
{
	char **mapptr = new char*[30];//2d array declared with pointers
	for (int i = 0; i < 30; ++i)
	{
		mapptr[i] = new char[101];
	}
	
	

	int rowcounter = 0;
	int colcounter = 0;
	int entercounter = 0;
	int totaldimen = 3000;

	while (rowcounter < 30)
	{
		while (colcounter < 101)
		{
			while (int i = 0 != totaldimen)
			{
				mapptr[rowcounter][colcounter] = levelgen()[i];
				i++;
				colcounter++;
			}
			rowcounter++;
			colcounter = 0;
		}
	}
	map = mapptr;
	
}

char** getarray(void)
{
	return map;
}


bool collision(char array[30][101], int playerycoord, int playerxcoord) //checks if player encounters a wall
{
	if (array[playerycoord][playerxcoord] == (char)219)//up
	{
		return true;
	}
	else
	{
		return false;
	}
}	

bool touchmonster(char array[30][101], int playerycoord, int playerxcoord)//checks if player encounters a monster
{
	if (array[playerycoord][playerxcoord] == 'm')
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool touchkey(char array[30][101], int playerycoord, int playerxcoord)//checks if player encounters a key
{
	if (array[playerycoord][playerxcoord] == 'k')
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool touchend(char array[30][101], int playerycoord, int playerxcoord)//checks if player encounters the end of the level
{
	if (array[playerycoord][playerxcoord] == 'o')
	{
		return true;
	}
	else
	{
		return false;
	}
}

