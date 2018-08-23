#pragma once
#ifndef TILEMANAGER_H
#define TILEMANAGER_H

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

void arraymaker(string levelgen());
bool collision(char array[30][100], int playerycoord, int playerxcoord);
char** getarray(void);
bool touchmonster(char array[30][100], int playerycoord, int playerxcoord);
bool touchkey(char array[30][100], int playerycoord, int playerxcoord);
bool touchend(char array[30][100], int playerycoord, int playerxcoord);


#endif