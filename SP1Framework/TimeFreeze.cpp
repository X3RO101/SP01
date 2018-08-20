#include "TimeFreeze.h"

bool timeFreeze( EGAMESTATES  g_eGameState/*, int * HP  */) // run infinitely until timer runs out
{
	bool done = true;
	CStopWatch time; // this makes a stopwatch
	time.startTimer(); //start stopwatch
	double durationPassed = time.getElapsedTime(); // gets the time that has passed
	while (done)
	{

		durationPassed += time.getElapsedTime(); // keeps updating the time passed
		if (durationPassed > 10.0)
		{
			done = false;
			g_eGameState = S_GAME;
		}

	}
	return true;
}/*
    if (/*userInput ==  Mob->correctAns) // when player gets it correct
	{
		//x = false;
		//change gamestate back
	}
	else if (/*userInput !=  Mob->correctAns) //when they input wrong answer
	{
		//*HP--;
	}
	//return x;
	*/

