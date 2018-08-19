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
	srand(time(nullptr)); // so that each playthrough wil lhave different dummy keys
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
	5.Initialise all the keys/dummy keys
	6.Make a function so that each level will choose a set of keys and question for the door
	6.5 Basically call this function when u enter a level

	OTHER THINGS TO NOTE:
	How to connect the keys and mobs to wallace's mobs and key gen?
	well:
	1.Make counters for keys and mobs that reset each level < --- safety measure
	2.Check if the counter is less than the amount of the entity(keys for now) in the level when they run into a key
	3.Flip a coin(aka random numbner between 1 and 2) to see if its the correct password or a dummy password
	4.Afterwards increase counter and print out the text
	4.5 Make sure that the frame freezes i guess another gamestate to let the player read the key password
*/