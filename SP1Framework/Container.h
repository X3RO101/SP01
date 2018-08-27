#pragma once
#ifndef CONTAINER_H
#define CONTAINER_H
#include <iostream>
#include <string>
//this header used for including in other header files where the cpp needs definitions
int monsterslain(struct SGameChar g_sChar, struct monstatus monster[]);
extern struct SGameChar g_sChar;
extern struct monstatus monster[7];

using namespace std;

struct SGameChar
{
	COORD m_cLocation;
	bool  m_bActive;
};

struct monstatus
{
	COORD location;
	bool alive;
};

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
