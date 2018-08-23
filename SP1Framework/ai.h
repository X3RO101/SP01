#pragma once
#ifndef AI_H
#define AI_H

#include <iostream>
#include <vector>
#include <fstream>
#include <stdio.h>

using namespace std;

struct monsterinfo
{
	int monycoord;
	int monxcoord;
	bool alive;
};

vector<int> monloca;

void findmonster(monsterinfo * coord);

#endif
