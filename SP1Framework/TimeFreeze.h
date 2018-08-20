#pragma once
#ifndef TIME_FREEZE_H
#define TIME_FREEZE_H
#include <iostream>
#include <string>
#include <fstream>
#include <chrono>
#include <ctime>
#include "Framework/timer.h"
#include "game.h"
#include "TextStore.h"

using namespace std;

bool timeFreeze(EGAMESTATES g_eGameState/*, int * HP  */);

#endif // !TIME_FREEZE_H
