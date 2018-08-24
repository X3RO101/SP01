#pragma once
#ifndef COMBAT_H
#define COMBAT_H
#include <iostream>
#include <string>
#include <fstream>
#include <random>
#include <ctime>
#include "Framework/console.h"
using namespace std;
// functions in the combatRender.cpp are the logic and initialisations
// rendering text shall be in game.cpp
struct Text
{
	string monsterQn;
};


//functions that render combat text/store and initialise text

void initMobText(Text * mobNo, ifstream* mobFile); // to be used in intialise
void textPicker();
void spamPrint();
void inputAns();
void checkAns();
void ansWrong();
void combatlogic(); // inputAns checkAns and ansWrong all in here
void printCOrW();
void stopPrintingCOrW(double dt);

#endif // !COMBAT_H
