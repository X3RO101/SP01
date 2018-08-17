#include "TextStore.h"
#include "game.h"

void textBank(Text * mob, ifstream * mobInfo)
{
	string ansr;
	getline(*mobInfo, mob->monsterName);
	getline(*mobInfo, mob->monsterQn);
	getline(*mobInfo, mob->ans1);
	getline(*mobInfo, mob->ans2);
	getline(*mobInfo, mob->ans3);
	getline(*mobInfo, ansr);
	mob->correctAns = stoi(ansr);
}
