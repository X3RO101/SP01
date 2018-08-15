#include "RenderText.h"

string WhichText(char entity) // function called when mob/key/door is interacted with
{
	string textToRender;
	char entityInput = entity;
	string result;
	switch (entityInput) // switch case to see which one is it
	{
	case 'm':
		textToRender = "testline.txt";
		break;
	case 'k':
		textToRender = "testline2.txt";
		break;
	default:
		textToRender = "\0";
		break;
	}

	result = RenderText(textToRender); // calls this function to get the content of the io file

	return result;
}


string RenderText(string WhichToRender)
{
	ifstream RenderThisText;
	RenderThisText.open(WhichToRender, ios::out);

	string returnText;
	char currentC;
	string temp;
	for (int i = 0; i < 5; i++)
	{
		getline(RenderThisText, temp);
		for (int j = 0; j < temp.length(); j++)
		{
			currentC = temp[j];
			if (currentC == temp[j])
			{
				returnText += currentC;
			}
			if (temp[j + 1] == '\0')
			{
				returnText += ' ';
			}
		}
		returnText += ' ';
	}
	return returnText;
}