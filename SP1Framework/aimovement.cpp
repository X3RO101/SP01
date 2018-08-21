#include "game.h"
#include "Framework\console.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <string>
#include <stdio.h>

using namespace std;
#include "collision.h"
#include "TextStore.h"
#include "tilemanager.h"
#include "Keys.h"
#include <ctime>
#include <random>

char aimoves(char map[15][87], SGameChar g_sChar, monstatus monster)
{
	COORD path;
	path.X = monster.location.X;
	path.Y = monster.location.Y;
	string pathchar;
	bool up = false;
	bool down = false;
	bool left = false;
	bool right = false;
	if (collision(map, (path.Y + 1), path.X) != true)
	{
		
	}
	else if (collision(map, path.Y, (path.X + 1)) != true)
	{

	}
	else if (collision(map, (path.Y - 1), path.X) != true)
	{
		
	}
	else if (collision(map, path.Y, (path.X - 1)) != true)
	{

	}
	return pathchar[0];
}