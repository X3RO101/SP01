/*#include <iostream>
#include "Levels.h"
#include <fstream>

using namespace std;

void Level_Gen(result)
{
	ifstream TestLevel;
	TestLevel.open("testmap.txt"); // TO DO : get height and width of level
    // --  make it point to build that level hen player selects level
	// make it build that level by replacing stuff in the text file
	
	int width = 0;
	int height = 0;
	string widthInput, heightInput;
	getline(TestLevel, widthInput);
	getline(TestLevel, heightInput);
	width = stoi(widthInput);
	height = stoi(heightInput);
	char ** result = new char*[height];//making 2d array
	for (char i = 0; i < height; ++i)
	{
		result[i] = new char[width];
	}
	
	char *ptr = &result[0][0];//pointer to 2d array 

	for (int i = 0; i < height - 1; i++)
	{
		string current;
		char currentChar;
		getline(TestLevel, current);
		for (int j = 0; j < width - 1; j++)
		{
			currentChar = current[j];
			switch (currentChar)
			{
			case '#':
				*ptr += '/';
				break;
			case 'k':
				*ptr += 'k';
				break;
			case 'o':
				*ptr += 'o';
				break;
			case 'x':
				*ptr += 'x';
				break;
			default:
				*ptr += ' ';
				break;
			}
		}
		*ptr += '\n';
	}
	
}*/