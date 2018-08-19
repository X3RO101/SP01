#include "Keys.h"

void KeyStore(ifstream * KeyFile, Key * KeyItem) //For Correct Password
{
	getline(*KeyFile, KeyItem->KeyText);
}

void DummyKeys(ifstream * DummyKeys, Key * KeyItem) //Dummy Keys
{
	getline(*DummyKeys, KeyItem->KeyText);
}

string WhichKey(string * keyGiven, bool *kArray) // for the dummy keys
{
	srand(time(nullptr));
	bool doneGiven; // make sure that the key is not repeated
	while (doneGiven)
	{
		int k;
		k = rand() % 10 + 1;// change the 10 to the number of keys later;
		if (kArray[k - 1]) // checks if the key has not been printed out yet
		{
			switch (k) // add the keys here later
			{
			default:
				break;
			}
			kArray[k - 1] = false;
		}
		doneGiven = false;
	}
	return *keyGiven;
}
/* Things to note:
	1.Text File for actual password for keys
	2.switch case for the level to get the levels correct password from text file
	3.SEPERATE TEXT FILE for dummy key passwords
	4.Make an array similar to the random mob gen for the dummy keys
*/