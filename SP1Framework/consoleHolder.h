#pragma once
#ifndef CONSOLEHOLDER_H
#define CONSOLEHOLDER_H
#include <iostream>
#include <string>
#include "Framework/console.h"

void getConsole(Console con);

enum EGAMESTATES
{
	S_SPLASHSCREEN,
	S_GAME,
	S_COUNT,
	S_COMBAT,

};

Console g_Console(87, 30, "SP1 Framework");
EGAMESTATES g_eGameState = S_SPLASHSCREEN;



#endif // !CONSOLEHOLDER_H
