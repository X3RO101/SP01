#include "combat.h"

double totalTime = 0;

void combat(EGAMESTATES GameState, double deltaTime) //runs all the combat function
{
	duration(deltaTime, &GameState);
}

void renderCombat(bool *BoolArray, Console conCommands)
{
	textRender(BoolArray, conCommands);
}

void processAnsInput()
{

}

void duration(double elapsed, EGAMESTATES *GameState)
{
	totalTime += elapsed;

	if (totalTime > 3.0)
	{
		*GameState = S_GAME;
	}
}

void textRender(bool *BoolArray, Console conCommands)
{
	const WORD colors[] = {
		0x1A, 0x2B, 0x3C, 0x4D, 0x5E, 0x6F,
		0xA1, 0xB2, 0xC3, 0xD4, 0xE5, 0xF6
	};

	COORD textCoord;
	textCoord.X = 0;
	textCoord.Y = 18;
	string output;


	conCommands.writeToBuffer(textCoord, randMobText(&output, BoolArray), colors[0]);
}

string randMobText(string *output, bool *BoolArray)
{
	bool done = true;
	while (done)
	{
		int a = rand() % 18 + 1;
		if (BoolArray[a - 1])
		{
			switch (a)
			{
			case 1:
			{
				*output += Monster1.monsterName;
				*output += ' ';
				*output += Monster1.monsterQn;
				*output += ' ';
				*output += Monster1.ans1;
				*output += ' ';
				*output += Monster1.ans2;
				*output += ' ';
				*output += Monster1.ans3;

			}
			break;
			case 2:
				*output += Monster2.monsterName;
				*output += ' ';
				*output += Monster2.monsterQn;
				*output += ' ';
				*output += Monster2.ans1;
				*output += ' ';
				*output += Monster2.ans2;
				*output += ' ';
				*output += Monster2.ans3;
				break;
			case 3:
				*output += Monster3.monsterName;
				*output += ' ';
				*output += Monster3.monsterQn;
				*output += ' ';
				*output += Monster3.ans1;
				*output += ' ';
				*output += Monster3.ans2;
				*output += ' ';
				*output += Monster3.ans3;
				break;
			case 4:
				*output += Monster4.monsterName;
				*output += ' ';
				*output += Monster4.monsterQn;
				*output += ' ';
				*output += Monster4.ans1;
				*output += ' ';
				*output += Monster4.ans2;
				*output += ' ';
				*output += Monster4.ans3;
				break;
			case 5:
				*output += Monster5.monsterName;
				*output += ' ';
				*output += Monster5.monsterQn;
				*output += ' ';
				*output += Monster5.ans1;
				*output += ' ';
				*output += Monster5.ans2;
				*output += ' ';
				*output += Monster5.ans3;
				break;
			case 6:
				*output += Monster6.monsterName;
				*output += ' ';
				*output += Monster6.monsterQn;
				*output += ' ';
				*output += Monster6.ans1;
				*output += ' ';
				*output += Monster6.ans2;
				*output += ' ';
				*output += Monster6.ans3;
				break;
			case 7:
				*output += Monster7.monsterName;
				*output += ' ';
				*output += Monster7.monsterQn;
				*output += ' ';
				*output += Monster7.ans1;
				*output += ' ';
				*output += Monster7.ans2;
				*output += ' ';
				*output += Monster7.ans3;
				break;
			case 8:
				*output += Monster8.monsterName;
				*output += ' ';
				*output += Monster8.monsterQn;
				*output += ' ';
				*output += Monster8.ans1;
				*output += ' ';
				*output += Monster8.ans2;
				*output += ' ';
				*output += Monster8.ans3;
				break;
			case 9:
				*output += Monster9.monsterName;
				*output += ' ';
				*output += Monster9.monsterQn;
				*output += ' ';
				*output += Monster9.ans1;
				*output += ' ';
				*output += Monster9.ans2;
				*output += ' ';
				*output += Monster9.ans3;
				break;
			case 10:
				*output += Monster10.monsterName;
				*output += ' ';
				*output += Monster10.monsterQn;
				*output += ' ';
				*output += Monster10.ans1;
				*output += ' ';
				*output += Monster10.ans2;
				*output += ' ';
				*output += Monster10.ans3;
				break;
			case 11:
				*output += Monster11.monsterName;
				*output += ' ';
				*output += Monster11.monsterQn;
				*output += ' ';
				*output += Monster11.ans1;
				*output += ' ';
				*output += Monster11.ans2;
				*output += ' ';
				*output += Monster11.ans3;
				break;
			case 12:
				*output += Monster12.monsterName;
				*output += ' ';
				*output += Monster12.monsterQn;
				*output += ' ';
				*output += Monster12.ans1;
				*output += ' ';
				*output += Monster12.ans2;
				*output += ' ';
				*output += Monster12.ans3;
				break;
			case 13:
				*output += Monster13.monsterName;
				*output += ' ';
				*output += Monster13.monsterQn;
				*output += ' ';
				*output += Monster13.ans1;
				*output += ' ';
				*output += Monster13.ans2;
				*output += ' ';
				*output += Monster13.ans3;
				break;
			case 14:
				*output += Monster14.monsterName;
				*output += ' ';
				*output += Monster14.monsterQn;
				*output += ' ';
				*output += Monster14.ans1;
				*output += ' ';
				*output += Monster14.ans2;
				*output += ' ';
				*output += Monster14.ans3;
				break;
			case 15:
				*output += Monster15.monsterName;
				*output += ' ';
				*output += Monster15.monsterQn;
				*output += ' ';
				*output += Monster15.ans1;
				*output += ' ';
				*output += Monster15.ans2;
				*output += ' ';
				*output += Monster15.ans3;
				break;
			case 16:
				*output += Monster16.monsterName;
				*output += ' ';
				*output += Monster16.monsterQn;
				*output += ' ';
				*output += Monster16.ans1;
				*output += ' ';
				*output += Monster16.ans2;
				*output += ' ';
				*output += Monster16.ans3;
				break;
			case 17:
				*output += Monster17.monsterName;
				*output += ' ';
				*output += Monster17.monsterQn;
				*output += ' ';
				*output += Monster17.ans1;
				*output += ' ';
				*output += Monster17.ans2;
				*output += ' ';
				*output += Monster17.ans3;
				break;
			case 18:
				*output += Monster18.monsterName;
				*output += ' ';
				*output += Monster18.monsterQn;
				*output += ' ';
				*output += Monster18.ans1;
				*output += ' ';
				*output += Monster18.ans2;
				*output += ' ';
				*output += Monster18.ans3;
				break;
			default:
				break;
			}

			BoolArray[a - 1] = false;
		}
		done = false;
	}
	return *output;
}