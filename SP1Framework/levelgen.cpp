/*#include "levelgen.h"

string levelgen()
{
	ifstream testlevel;
	testlevel.open("testmap.txt");

	int width = 0;
	int height = 0;
	string widthinput, heightinput;
	getline(testlevel, widthinput);
	getline(testlevel, heightinput);
	width = stoi(widthinput);
	height = stoi(heightinput);
	string result;
	for (int i = 0; i < height - 1; i++)
	{
		string current;
		char currentchar;
		getline(testlevel, current);
		for (int j = 0; j < width - 1; j++)
		{
			currentchar = current[j];
			switch (currentchar)
			{
			case '#':
				result += 219;
				break;
			case 'k':
				result += 'k';
				break;
			case 'o':
				result += 'o';
				break;
			case 'x':
				result += 'x';
				break;
			default:
				result += ' ';
				break;
			}
		}
		result += '\n';
	}

	return result;
}*/