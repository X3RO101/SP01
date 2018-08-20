#pragma once
#ifndef COMBAT_H
#define COMBAT_H

#include<iostream>
#include<string>
#include<fstream>
#include "game.h"
#include "Framework/timer.h"

using namespace std;

void combat(EGAMESTATES * GameState,double deltaTime);
void processAnsInput();
void duration(double elapsed, EGAMESTATES *GameState);
bool disableMove(EGAMESTATES * GameState);
void renderText(string *mobText);
void renderCombat();


#endif