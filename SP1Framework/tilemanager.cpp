#include "tilemanager.h"

char **map;

void arraymaker(string levelgen())
{
	char **mapptr = new char*[15];//2d array declared with pointers
	for (int i = 0; i < 15; ++i)
	{
		mapptr[i] = new char[87];
	}
	
	

	int rowcounter = 0;
	int colcounter = 0;
	int entercounter = 0;
	int totaldimen = 1305;

	while (rowcounter < 15)
	{
		while (colcounter < 87)
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

bool collision(char array[15][87], int playerycoord, int playerxcoord) //checks if player encounters a wall
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


bool touchmonster(char array[15][87], int playerycoord, int playerxcoord)//checks if player encounters a monster
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

bool touchkey(char array[15][87], int playerycoord, int playerxcoord)//checks if player encounters a key
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

bool touchend(char array[15][87], int playerycoord, int playerxcoord)//checks if player encounters the end of the level
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
