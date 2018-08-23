#include "TextStore.h"

void textBank(Text mob, ifstream * mobInfo)
{
	string ansr;
	getline(*mobInfo, mob.monsterQn);
	getline(*mobInfo, ansr);
	mob.correctAns = ansr[0];
}
