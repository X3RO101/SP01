#include "TextChanger.h"

char TextChanger(char input)
{

	char CharReturn;
	switch (input)
	{
	case 'k':
		CharReturn = 'k';
		break;
	case 'o':
		CharReturn = 'o';
		break;
	case 'm':
		CharReturn = 'm';
		break;
	default:
		CharReturn = 'z';
		break;
	}

	return CharReturn;
}
