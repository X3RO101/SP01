#pragma once
#ifndef TEXT_STORE_H
#define TEXT_STORE_H
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

struct Text
{
	string monsterName;
	string monsterQn;
	string ans1;
	string ans2;
	string ans3;
	char correctAns;
};

void textBank(Text * text, ifstream * mobInfo);


#endif // !TEXT_STORE_H
