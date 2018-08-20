#pragma once
#ifndef COMBAT_H
#define COMBAT_H

#include<iostream>
#include<string>
#include<fstream>
#include "Framework/timer.h"
#include "TextStore.h"
#include "consoleHolder.h"

using namespace std;

void combat(EGAMESTATES GameState, double deltaTime);
void duration(double elapsed, EGAMESTATES *GameState);
string randMobText(string *mobText, bool *BoolArray);
void renderCombat(bool *BoolArray, Console conCommands);
void processAnsInput();
void textRender(bool *BoolArray, Console conCommands);


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

#endif