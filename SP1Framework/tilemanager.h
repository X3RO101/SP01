#pragma once
#ifndef TILEMANAGER_H
#define TILEMANAGER_H

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

void arraymaker(string levelgen());
char** getarray(void);
//bool touchmonster(char array[15][87], int playerycoord, int playerxcoord);

bool touchmonster(struct SGameChar g_sChar, struct monstatus monster[]);
bool monstercollides(int i, struct monstatus monster[]);
int monsterslain(struct SGameChar g_sChar, struct monstatus monster[]);
bool collision(char array[30][101], int playerycoord, int playerxcoord);
char** getarray(void);
bool touchkey(char array[30][101], int playerycoord, int playerxcoord);
bool touchend(char array[30][101], int playerycoord, int playerxcoord);
bool touchplayer(struct monstatus monster[], struct SGameChar g_sChar, int i);


#endif