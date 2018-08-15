#include "UserAnswer.h"


void answerChecker(char mobQn, string ans)
{
	CStopWatch time;
	time.startTimer();
	double durationPassed = time.getElapsedTime();

	/*auto start = std::chrono::system_clock::now();
	std::chrono::time_point<std::chrono::system_clock> startPoint = start;
	std::chrono::duration<int> elapsedTime;*/
	while (true)
	{
		durationPassed += time.getElapsedTime();
		if (durationPassed > 10.0)
		{
			//game over screen
			break;
		}
		if (true)//ans correct
		{
			//point += 100;
			break;
		}
		if (true)// ans wrong
		{
			//HP -= 1;
		}
	}
}

string ansInput(string input)
{
	return 0;
}