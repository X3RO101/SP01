#pragma once
#ifndef COMBAT_H
#define COMBAT_H

#include<iostream>
#include<string>
#include<fstream>
#include "TextStore.h"
#include "Framework/console.h"
#include "Framework/timer.h"

using namespace std;


// =================THE MOBS=============================
Text Monster1;
Text Monster2;
Text Monster3;
Text Monster4;
Text Monster5;
Text Monster6;
Text Monster7;
Text Monster8;
Text Monster9;
Text Monster10;
Text Monster11;
Text Monster12;
Text Monster13;
Text Monster14;
Text Monster15;
Text Monster16;
Text Monster17;
Text Monster18;
// =================END OF THE MOBS=======================

enum EGAMESTATES
{
	S_SPLASHSCREEN,
	S_GAME,
	S_COUNT,
	S_COMBAT,
};


EGAMESTATES g_eGameState;



void combat(EGAMESTATES GameState, double deltaTime);
void duration(double elapsed, EGAMESTATES *GameState);
void renderCombat(bool *BoolArray, Console conCommands);
string randMobText(string *mobText, bool *BoolArray);
void processAnsInput();
void textRender(bool *BoolArray, Console conCommands);

#endif