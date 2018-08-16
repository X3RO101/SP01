#pragma once
#ifndef TILEMANAGER_H
#define TILEMANAGER_H

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

void arraymaker(string levelgen());
bool collision(char array[15][87], int playerycoord, int playerxcoord);
char** getarray(void);


#endif