#include "combat.h"

CStopWatch timer;
bool exitCombat = false;
double totalTime = 0;
double deltaTimer;

void combat(EGAMESTATES * GameState, double deltaTime) //runs all the combat function
{
	duration(deltaTime, GameState);
}

void renderCombat()
{

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

bool disableMove(EGAMESTATES * GameState)
{
	if (*GameState == S_COMBAT)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void renderText(string *mobText)
{

}