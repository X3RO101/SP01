#pragma once
#ifndef TILEMANAGER_H
#define TILEMANAGER_H

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

char** arraymaker(string levelgen());
bool collision(char **array, int playerycoord, int playerxcoord);
char ** getarray(void);


#endif