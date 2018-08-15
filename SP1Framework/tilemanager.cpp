#include "tilemanager.h"

char **map;

char** arraymaker(string levelgen())
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
	return mapptr;
}

char **getarray(void)
{
	return map;
}

bool collision(char **array, int playerycoord, int playerxcoord)
{
	if (array[playerycoord][playerxcoord] == 219)
	{
		return true;
	}
	else
	{
		return false;
	}
}

