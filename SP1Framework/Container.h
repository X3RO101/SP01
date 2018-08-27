#pragma once
#ifndef CONTAINER_H
#define CONTAINER_H
#include <iostream>
#include <string>

using namespace std;

// Enumeration to store the control keys that your game will have
enum EKEYS
{
	K_UP,
	K_DOWN,
	K_LEFT,
	K_RIGHT,
	K_ESCAPE,
	K_SPACE,
	K_1,
	K_2,
	K_3,
	K_COUNT
};

// Enumeration for the different screen states
enum EGAMESTATES
{

	S_SPLASHSCREEN,
	S_CONTROLS,
	S_GAME,
	S_COUNT,
	S_DEATH,
	S_PAUSE,
	S_COMBAT,
	S_DIFFICULTY,
	S_COMBATAFTERMATH
};


#endif // !CONTAINER_H
