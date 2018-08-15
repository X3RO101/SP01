#ifndef MOB_SPAWN_H
#define MOB_SPAWN_H

#include<iostream>
#include<random>
#include<ctime>
#include<string>
#include<cmath>

using namespace std;

char SetLocation(char ySet[4], char xSet[4]);
char** MapLocation();
bool LocationCheck(char(*CheckArray)[4][4]);

#endif /* MOB_SPAWN_H */
