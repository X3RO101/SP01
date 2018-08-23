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
void textPicker(string * input,bool * boolarray, int * passer);
void spamPrint(string input);
void ansChecker(int passer, string mobAns);
void initAns(ifstream * mobans, string * ansStr);

#endif // !COMBAT_H
