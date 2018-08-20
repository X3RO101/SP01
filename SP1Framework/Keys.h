#pragma once
#ifndef KEYS_H
#define KEYS_H
#include <iostream>
#include <string>
#include <fstream>
#include <random>
#include <ctime>

using namespace std;

struct Key
{
	string KeyText;
};

void KeyStore(ifstream * KeyFile, Key * KeyItem);
void DummyKeys(ifstream * DummeyKeys, Key * KeyItem);
string WhichKey(string * keyGiven, bool *kArray);


#endif // !KEYS_H

