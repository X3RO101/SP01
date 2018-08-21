#include "combatRender.h"


void initMobText(Text * mobNo, ifstream* mobFile)
{
	getline(*mobFile, mobNo->monsterQn); // stores the mob text into the mob object 
}

