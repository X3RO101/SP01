#pragma once
#ifndef COMBAT_H
#define COMBAT_H
#include <iostream>
#include <string>
#include <fstream>
#include <random>
#include <ctime>
#include "Framework/console.h"
#include "Container.h"

using namespace std;
// functions in the combatRender.cpp are the logic and initialisations
// rendering text shall be in game.cpp
struct Text
{
	string monsterQn;
};

extern Console g_Console;
extern bool moveAllow;
extern enum EGAMESTATES g_eGameState;
extern bool isdead;
extern enum EKEYS;
extern bool g_abKeyPressed[K_COUNT];
extern void getInput();

extern struct SGameChar g_sChar;
extern struct monstatus monster[7];

//functions that render combat text/store and initialise text

void initMobText(Text * mobNo, ifstream* mobFile); // to be used in intialise
void textPicker();
void spamPrint();
void inputAns();
void checkAns();
void ansWrong();

void combatlogic();
void printCOrW();
void stopPrintingCOrW(double dt);
void combatlogic(); // inputAns checkAns and ansWrong all in here
void printCOrW();
void stopPrintingCOrW(double dt);
void duration(EGAMESTATES * gameState, double dt); // timer for the mob encounters
void COMBAT(); // textPicker and spamPrint inside

#endif // !COMBAT_H
