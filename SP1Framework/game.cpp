// This is the main file for the game logic and function
//
//
#include "game.h"
#include "Framework\console.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <string>
#include <stdio.h>

using namespace std;
#include "collision.h"
#include "TextStore.h"
#include "tilemanager.h"
#include "Keys.h"
#include <ctime>
#include <random>

int lvlcleared = 1;
int changeinlvl = 1;

char map[15][87];


void textRender();
bool bArray[18]; // bool array for random mob gen so that it doesnt print twice
bool kArray[10]; // bool array for random DUMMY KEYs so they dont spawn twice (number inside [] tbd)

double  g_dElapsedTime;
double  g_dDeltaTime;
bool    g_abKeyPressed[K_COUNT];

bool isdead = false;				// bool when player loses to the mob once
bool killmob = false;				// bool for when player kills the mob
int healthpoints = 3;				// number of lives player has
int score = 0;						// player score
bool main_menu_1 = true;			// to check if player is choosing the start option
bool main_menu_2 = false;			// to check if player is choosing the controls option
bool pause_1 = true;				// to check if player is choosing continue
bool pause_2 = false;				// to check if player is choosing to go to main menu
bool pause_3 = false;				// to check if player is choosing to exit game
int keycount = 0;

// Game specific variables here
SGameChar   g_sChar;
//  MOB Text copy
Text Monster1;
Text Monster2;
Text Monster3;
Text Monster4;
Text Monster5;
Text Monster6;
Text Monster7;
Text Monster8;
Text Monster9;
Text Monster10;
Text Monster11;
Text Monster12;
Text Monster13;
Text Monster14;
Text Monster15;
Text Monster16;
Text Monster17;
Text Monster18;
ifstream mobInfo("MobsFinal.txt");
// MOB Text copy
// KEY TEXT
ifstream CorrectPass("CorrectPasswords.txt");
Key L1K1;
// KEY TEXT
// DUMMY KEYS
ifstream DummyFile("DummyKeys.txt");
Key Dummy1;
// DUMMY KEYS
string texty;
string whichText(string *output, bool *boolArray);

EGAMESTATES g_eGameState = S_SPLASHSCREEN;
double  g_dBounceTime; // this is to prevent key bouncing, so we won't trigger keypresses more than once

// Console object
Console g_Console(87, 30, "                                                             Labyrinthos Libertas");

//--------------------------------------------------------------
// Purpose  : Initialisation function
//            Initialize variables, allocate memory, load data from file, etc. 
//            This is called once before entering into your main loop
// Input    : void
// *output   : void
//--------------------------------------------------------------
void init( void )
{
    // Set precision for floating point *output
    g_dElapsedTime = 0.0;
    g_dBounceTime = 0.0;

    // sets the initial state for the game
    g_eGameState = S_SPLASHSCREEN;

    g_sChar.m_cLocation.X = g_Console.getConsoleSize().X / 2;
    g_sChar.m_cLocation.Y = 5;
    g_sChar.m_bActive = true;
    // sets the width, height and the font name to use in the console
    g_Console.setConsoleFont(16, 0, L"Consolas");
	textBank(&Monster1, &mobInfo);
	textBank(&Monster2, &mobInfo);
	textBank(&Monster3, &mobInfo);
	textBank(&Monster4, &mobInfo);
	textBank(&Monster5, &mobInfo);
	textBank(&Monster6, &mobInfo);
	textBank(&Monster7, &mobInfo);
	textBank(&Monster8, &mobInfo);
	textBank(&Monster9, &mobInfo);
	textBank(&Monster10, &mobInfo);
	textBank(&Monster11, &mobInfo);
	textBank(&Monster12, &mobInfo);
	textBank(&Monster13, &mobInfo);
	textBank(&Monster14, &mobInfo);
	textBank(&Monster15, &mobInfo);
	textBank(&Monster16, &mobInfo);
	textBank(&Monster17, &mobInfo);
	textBank(&Monster18, &mobInfo);      
	for (int i = 0; i < sizeof(bArray); i++)  // initialise all the memory to be true for the mobs' text
	{
		bArray[i] = true;
	}

	for (int i = 0; i < sizeof(kArray); i++)  // same goes for the keys
	{
		kArray[i] = true;
	}
}

//--------------------------------------------------------------
// Purpose  : Reset before exiting the program
//            Do your clean up of memory here
//            This is called once just before the game exits
// Input    : Void
// *output   : void
//--------------------------------------------------------------
void shutdown( void )
{
    // Reset to white text on black background
    colour(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);

    g_Console.clearBuffer();
}

//--------------------------------------------------------------
// Purpose  : Getting all the key press states
//            This function checks if any key had been pressed since the last time we checked
//            If a key is pressed, the value for that particular key will be true
//
//            Add more keys to the enum in game.h if you need to detect more keys
//            To get other VK key defines, right click on the VK define (e.g. VK_UP) and choose "Go To Definition" 
//            For Alphanumeric keys, the values are their ascii values (uppercase).
// Input    : Void
// *output   : void
//--------------------------------------------------------------
void getInput( void )
{    
    g_abKeyPressed[K_UP]     = isKeyPressed(VK_UP);
    g_abKeyPressed[K_DOWN]   = isKeyPressed(VK_DOWN);
    g_abKeyPressed[K_LEFT]   = isKeyPressed(VK_LEFT);
    g_abKeyPressed[K_RIGHT]  = isKeyPressed(VK_RIGHT);
    g_abKeyPressed[K_SPACE]  = isKeyPressed(VK_SPACE);
    g_abKeyPressed[K_ESCAPE] = isKeyPressed(VK_ESCAPE);
	g_abKeyPressed[K_1]      = isKeyPressed(0x31);
	g_abKeyPressed[K_2]      = isKeyPressed(0x32);
	g_abKeyPressed[K_3]      = isKeyPressed(0x33);
}

//--------------------------------------------------------------
// Purpose  : Update function
//            This is the update function
//            double dt - This is the amount of time in seconds since the previous call was made
//
//            Game logic should be done here.
//            Such as collision checks, determining the position of your game characters, status updates, etc
//            If there are any calls to write to the console here, then you are doing it wrong.
//
//            If your game has multiple states, you should determine the current state, and call the relevant function here.
//
// Input    : dt = deltatime
// *output   : void
//--------------------------------------------------------------
void update(double dt)
{
    // get the delta time
    g_dElapsedTime += dt;
    g_dDeltaTime = dt;

    switch (g_eGameState)
    {
        case S_SPLASHSCREEN : main_menu_option(); // game logic for the splash screen
            break;
        case S_GAME: gameplay(); // gameplay logic when we are in the game
            break;
		case S_DEATH: 
			break;
		case S_CONTROLS: control_screen_back();
			break;
		case S_PAUSE: pause_select();
			break;
		//case S_COMBAT :
    }
}
//--------------------------------------------------------------
// Purpose  : Render function is to update the console screen
//            At this point, you should know exactly what to draw onto the screen.
//            Just draw it!
//            To get an idea of the values for colours, look at console.h and the URL listed there
// Input    : void
// *output   : void
//--------------------------------------------------------------
void render()
{
    clearScreen();      // clears the current screen and draw from scratch 
    switch (g_eGameState)
    {
        case S_SPLASHSCREEN: renderSplashScreen();
            break;
        case S_GAME: renderGame();
            break;
		case S_CONTROLS: control_screen();
			break;
		case S_DEATH: game_over();
			break;
		case S_PAUSE: pause_screen();
			break;
    }
    renderFramerate();  // renders debug information, frame rate, elapsed time, etc
    renderToScreen();   // dump the contents of the buffer to the screen, one frame worth of game
}

void splashScreenWait()    // waits for time to pass in splash screen
{
    if (g_dElapsedTime > 3.0) // wait for 3 seconds to switch to game mode, else do nothing
        g_eGameState = S_GAME;
}

void gameplay()            // gameplay logic
{
    processUserInput(); // checks if you should change states or do something else with the game, e.g. pause, exit
    moveCharacter();    // moves the character, collision detection, physics, etc
                        // sound can be played here too.
	health();
	scoresystem();
}

void moveCharacter()
{
	COORD c;

	const WORD colors[] = {
		0x1A, 0x2B, 0x3C, 0x4D, 0x5E, 0x6F,
		0xA1, 0xB2, 0xC3, 0xD4, 0xE5, 0xF6
	};

    bool bSomethingHappened = false;
    if (g_dBounceTime > g_dElapsedTime)
        return;

    // Updating the location of the character based on the key press
    // providing a beep sound whenver we shift the character
    if ((g_abKeyPressed[K_UP] ) && (collision(map, (g_sChar.m_cLocation.Y - 1) , g_sChar.m_cLocation.X) != true))
    {
        //Beep(1440, 30);
        g_sChar.m_cLocation.Y--;
		if (touchmonster(map, g_sChar.m_cLocation.Y, g_sChar.m_cLocation.X) == true)
		{
			//run text for monster
		}
		else if (touchkey(map, g_sChar.m_cLocation.Y, g_sChar.m_cLocation.X) == true)
		{
			c.Y = g_sChar.m_cLocation.Y;
			c.X = g_sChar.m_cLocation.X;
			//run text for key
			map[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] = ' ';
			++keycount;
		}
		else if (touchend(map, g_sChar.m_cLocation.Y, g_sChar.m_cLocation.X) == true)
		{
			//run text for end door password, if correct, do lvlcleared++ to change lvl on next render, reset pos of player
			lvlcleared++;
			g_sChar.m_cLocation.X = g_Console.getConsoleSize().X / 2;
			g_sChar.m_cLocation.Y = 5;
			keycount = 0;
		}
        bSomethingHappened = true;
		
    }
   if ((g_abKeyPressed[K_LEFT]) && (collision(map, g_sChar.m_cLocation.Y, (g_sChar.m_cLocation.X - 1)) != true))//performs movement if keystroke is pressed and if there is no wall in the direction of travel
    {
	   g_Console.writeToBuffer(c, "Hello", colors[0]);
       // Beep(1440, 30);
        g_sChar.m_cLocation.X--;
		if (touchmonster(map, g_sChar.m_cLocation.Y, g_sChar.m_cLocation.X) == true)
		{
			//run text for monster
		}
		else if (touchkey(map, g_sChar.m_cLocation.Y, g_sChar.m_cLocation.X) == true)
		{
			c.Y = g_sChar.m_cLocation.Y;
			c.X = g_sChar.m_cLocation.X;
			//run text for key
			map[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] = ' ';
			keycount++;

			
		}
		else if (touchend(map, g_sChar.m_cLocation.Y, g_sChar.m_cLocation.X) == true)
		{
			//run text for end door password, if correct, do lvlcleared++ to change lvl on next render, reset pos of player
			lvlcleared++;
			g_sChar.m_cLocation.X = g_Console.getConsoleSize().X / 2;
			g_sChar.m_cLocation.Y = 5;
			keycount = 0;
		}
        bSomethingHappened = true;
    }
    if ((g_abKeyPressed[K_DOWN] ) && (collision(map, (g_sChar.m_cLocation.Y + 1) , g_sChar.m_cLocation.X) != true))
    {
        //Beep(1440, 30);
        g_sChar.m_cLocation.Y++;
		if (touchmonster(map, g_sChar.m_cLocation.Y, g_sChar.m_cLocation.X) == true)
		{
			//run text for monster
		}
		else if (touchkey(map, g_sChar.m_cLocation.Y, g_sChar.m_cLocation.X) == true)
		{
			c.Y = g_sChar.m_cLocation.Y;
			c.X = g_sChar.m_cLocation.X;
			//run text for key
			map[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] = ' ';
			keycount++;

		
		}
		else if (touchend(map, g_sChar.m_cLocation.Y, g_sChar.m_cLocation.X) == true)
		{
			//run text for end door password, if correct, do lvlcleared++ to change lvl on next render, reset pos of player
			lvlcleared++;
			g_sChar.m_cLocation.X = g_Console.getConsoleSize().X / 2;
			g_sChar.m_cLocation.Y = 5;
			keycount = 0;
		}
        bSomethingHappened = true;
    }
    if ((g_abKeyPressed[K_RIGHT] ) && (collision(map, g_sChar.m_cLocation.Y, (g_sChar.m_cLocation.X + 1)) != true))
    {
        //Beep(1440, 30);
        g_sChar.m_cLocation.X++;
		if (touchmonster(map, g_sChar.m_cLocation.Y, g_sChar.m_cLocation.X) == true)
		{
			//run text for monster
		}
		else if (touchkey(map, g_sChar.m_cLocation.Y, g_sChar.m_cLocation.X) == true)
		{
			c.Y = g_sChar.m_cLocation.Y;
			c.X = g_sChar.m_cLocation.X;
			//run text for key
			map[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] = ' ';
			keycount++;
		}
		else if (touchend(map, g_sChar.m_cLocation.Y, g_sChar.m_cLocation.X) == true)
		{
			//run text for end door password, if correct, do lvlcleared++ to change lvl on next render, reset pos of player
			lvlcleared++;
			g_sChar.m_cLocation.X = g_Console.getConsoleSize().X / 2;
			g_sChar.m_cLocation.Y = 5;
			keycount = 0;
		}
        bSomethingHappened = true;
    }
    if (g_abKeyPressed[K_SPACE])
    {
        g_sChar.m_bActive = !g_sChar.m_bActive;
        bSomethingHappened = true;
    }

    if (bSomethingHappened)
    {
        // set the bounce time to some time in the future to prevent accidental triggers
        g_dBounceTime = g_dElapsedTime + 0.015; // 125ms should be enough
    }
}
void processUserInput()
{
    // quits the game if player hits the escape key
    if (g_abKeyPressed[K_ESCAPE])
   /*     g_bQuitGame = true; */
		g_eGameState = S_PAUSE;
}

void clearScreen()
{
    // Clears the buffer with this colour attribute
    g_Console.clearBuffer(0x1F);
}

void renderSplashScreen()  // renders the splash screen
{
	main_menu();
/*
    COORD c = g_Console.getConsoleSize();
    c.Y /= 3;
    c.X = c.X / 2 - 9;
    g_Console.writeToBuffer(c, "Labyrinthos Libertas", 0x03); //Title of the game here
    c.Y += 1;
    c.X = g_Console.getConsoleSize().X / 2 - 20;
    g_Console.writeToBuffer(c, "Press <Space> to change character colour", 0x09);//color to change to if space bar is pressed
    c.Y += 1;
    c.X = g_Console.getConsoleSize().X / 2 - 9;
    g_Console.writeToBuffer(c, "Press 'Esc' to quit", 0x09);//quit
*/
}

void renderGame()
{
    renderMap();        // renders the map to the buffer first
    renderCharacter();  // renders the character into the buffer
	textRender();
}

void renderMap()
{
    //Set up sample colours, and output shadings
    const WORD colors[] = {
        0x1A, 0x2B, 0x3C, 0x4D, 0x5E, 0x6F,
        0xA1, 0xB2, 0xC3, 0xD4, 0xE5, 0xF6
    };


 /*   for (int i = 0; i < 12; ++i)
    {
        c.X = 5 * i;
        c.Y = i + 1;
        colour(colors[i]);
        g_Console.writeToBuffer(c, " °±²Û", colors[i]);
    } */
	
	string healthtext = "Health : ";
	COORD a;
	char currentchar;
	currentchar = 3;
	a.X = 1;
	a.Y = 15;
	for (int i = 0; i < 9; ++i)
	{
		g_Console.writeToBuffer(a, healthtext[i], 0x1A);
		a.X++;
	}
	for (int i = 0; i < healthpoints; ++i)
	{
		g_Console.writeToBuffer(a, currentchar, 0x1C);
		a.X++;
		g_Console.writeToBuffer(a, ' ', 0x1F);
		a.X++;
	}

	a.X = 1;
	a.Y = 16;
	string pointstext = "Score : ";
	ostringstream str1;
	str1 << score;
	string scorestr = str1.str();
	for (int i = 0; i < 8; ++i)
	{
		g_Console.writeToBuffer(a, pointstext[i], 0x1A);
		a.X++;
	}
	for (int i = 0; i < scorestr.length(); ++i)
	{
		g_Console.writeToBuffer(a, scorestr[i], 0x1A);
		a.X++;
	} 

	a.X = 18;
	a.Y = 15;
	string keystext = "Keys : ";
	char currentchar2;
	currentchar2 = 235;
	for (int i = 0; i < 7; ++i)
	{
		g_Console.writeToBuffer(a, keystext[i], 0x1A);
		a.X++;
	}
	for (int i = 0; i < keycount; ++i)
	{
		g_Console.writeToBuffer(a, currentchar2, 0x1A);
		a.X++;
		g_Console.writeToBuffer(a, ' ', 0x1F);
		a.X++;
	}
	
	colour(colors[0]);
    COORD c;
	string rows;
	string cols;
	string filename;
	int y;
	int x;

	if (lvlcleared == 1)
	{
		filename += "lvl1.txt";
	}
	else if (lvlcleared == 2)
	{
		filename += "lvl2.txt";
	}
	else if (lvlcleared == 3)
	{
		filename += "lvl3.txt";
	}
	else if (lvlcleared == 4)
	{
		filename += "lvl4.txt";
	}
	else if (lvlcleared == 5)
	{
		filename += "lvl5.txt";
	}


	if (lvlcleared == changeinlvl)
	{
		ifstream currentlvl;
		currentlvl.open(filename);
		getline(currentlvl, cols);
		getline(currentlvl, rows);
		y = stoi(rows);
		x = stoi(cols);

		for (int i = 0; i < y - 1; ++i)
		{
			string currentrow;
			char currentchar;
			getline(currentlvl, currentrow);
			for (int j = 0; j < x - 1; ++j)
			{
				currentchar = currentrow[j];

				c.X = j;
				c.Y = i;

				switch (currentchar)
				{
				case'#':
					map[i][j] = (char)219;

				//	g_Console.writeToBuffer(c, map[i][j], colors[0]);
					break;
				case'k':
					map[i][j] = 'k';
				//	g_Console.writeToBuffer(c, map[i][j], colors[0]);
					break;
				case'o':
					map[i][j] = 'o';
				//	g_Console.writeToBuffer(c, map[i][j], colors[0]);
					break;
				case'm':
					map[i][j] = 'm';
				//	g_Console.writeToBuffer(c, map[i][j], colors[0]);
					break;
				case ' ':
					map[i][j] = ' ';
				//	g_Console.writeToBuffer(c, map[i][j], colors[0]);			
					break;				

				default:
					break;

				}
			}
		}
		changeinlvl++;
		currentlvl.close();
	}
	else
	{
		for (int i = 0; i < 15; ++i)
		{
			for (int j = 0; j < 87; ++j)
			{
				c.X = j;
				c.Y = i;
				g_Console.writeToBuffer(c, map[i][j], colors[0]);
			}
		}
	}
}

void textRender()
{
	const WORD colors[] = {
		0x1A, 0x2B, 0x3C, 0x4D, 0x5E, 0x6F,
		0xA1, 0xB2, 0xC3, 0xD4, 0xE5, 0xF6
	};

	COORD Text;
	Text.X = 0;
	Text.Y = 17;
	g_Console.writeToBuffer(Text, whichText(&texty, &bArray[18]), colors[0]);

	/*start here
	
	filename;

	int lvlclear = 0;

	if (lvlclear == 0)
	{
		filename = "lvl1.txt";
	}
	else if (lvlclear == 1)
	{
		filename = "lvl2.txt";
	}


	ifstream currentlvl;
	currentlvl.open(filename);

	int width = 0;
	int height = 0;
	string widthinput, heightinput;
	getline(currentlvl, widthinput);
	getline(currentlvl, heightinput);
	width = stoi(widthinput);
	height = stoi(heightinput);
	string result;
	for (int i = 0; i < height - 1; i++)
	{
		string current;
		char currentchar;
		getline(currentlvl, current);
		

		for (int j = 0; j < width - 1; j++)
		{
			currentchar = current[j];
			switch (currentchar)
			{
			case '#':
				g_Console.writeToBuffer(c, 219, colors[i]);
				break;
			case 'k':
				g_Console.writeToBuffer(c, 'k', colors[i]);
				break;
			case 'o':
				g_Console.writeToBuffer(c, 'o', colors[i]);
				break;
			case 'x':
				g_Console.writeToBuffer(c, 'x', colors[i]);
				break;
			default:
				g_Console.writeToBuffer(c, ' ', colors[i]);
				break;
			}
		}
		g_Console.writeToBuffer(c, '\n', colors[i]);
	}
	
	end here*/
}

void renderCharacter()
{
    // Draw the location of the character
    WORD charColor = 0x0C;//default color of character
    if (g_sChar.m_bActive)//if spacebar is pressed, change the color of character
    {
        charColor = 0x0A;
    }
    g_Console.writeToBuffer(g_sChar.m_cLocation, (char)1, charColor);//send character printing details to the buffer
}

void renderFramerate()
{
    COORD c;
    // displays the framerate
    std::ostringstream ss;
    ss << std::fixed << std::setprecision(3);
    ss << 1.0 / g_dDeltaTime << "fps";
    c.X = g_Console.getConsoleSize().X - 9;
    c.Y = 0;
    g_Console.writeToBuffer(c, ss.str());

    // displays the elapsed time
    ss.str("");
    ss << g_dElapsedTime << "secs";
    c.X = 0;
    c.Y = 0;
    g_Console.writeToBuffer(c, ss.str(), 0x59);
}
void renderToScreen()
{
    // Writes the buffer to the console, hence you will see what you have written
    g_Console.flushBufferToConsole();
}

void game_over()
{
	//set a name to a string variable
	//ifstream file(note: file should be in the same folder as the err solution)
	//file.open(filename)
	//use the writeToBuffer (check the framework)

	char currentchar;
	COORD x;
	string gameoverscreen[6];
	gameoverscreen[0] = "  _______     ___     .___  ___. _______      ______  ____    ____ _______ .______  ";
	gameoverscreen[1] = " /  _____|   /   1    |   1/   ||   ____|    /  __  1 1   1  /   /|   ____||   _  1 ";
	gameoverscreen[2] = "|  |  __    /  ^  1   |  1  /  ||  |__      |  |  |  | 1   1/   / |  |__   |  |_)  |";
	gameoverscreen[3] = "|  | |_ |  /  /_1  1  |  |1/|  ||   __|     |  |  |  |  1      /  |   __|  |      / ";
	gameoverscreen[4] = "|  |__| | /  _____  1 |  |  |  ||  |____    |  `--'  |   1    /   |  |____ |  |1  1 ";
	gameoverscreen[5] = " 1______|/__/     1__1|__|  |__||_______|    1______/     1__/    |_______||__| `._|";

	for (int i = 0; i < 6; ++i)
	{
		for (int a = 0; a < 84; ++a)
		{
			x.X = a;
			x.Y = i + 1;
			currentchar = gameoverscreen[i][a];
			switch (currentchar)
			{
			case('1'):
				currentchar = 92;
				break;
			}
			g_Console.writeToBuffer(x, currentchar, 0x1A);
		}
	}
}



void main_menu()
{
	string main_menu_frame1[15];
	string main_menu_frame2[15];
	char currentchar;

	main_menu_frame1[0] =  "112     111112 1111112 112   1121111112 1121112   112111111112112  112 1111112 11111112";
	main_menu_frame1[1] =  "113    11755112117551124112 11761175511211311112  113455117556113  11311755511211755556";
	main_menu_frame1[2] =  "113    1111111311111176 4111176 11111176113117112 113   113   11111113113   11311111112";
	main_menu_frame1[3] =  "113    1175511311755112  41176  117551121131134112113   113   11755113113   11345555113";
	main_menu_frame1[4] =  "1111112113  11311111176   113   113  113113113 411113   113   113  11341111117611111113";
	main_menu_frame1[5] =  "4555556456  4564555556    456   456  456456456  45556   456   456  456 4555556 45555556";
	main_menu_frame1[6] =  "             112     1121111112 111111121111112 111111112 111112 11111112              ";
	main_menu_frame1[7] =  "             113     1131175511211755556117551124551175561175511211755556              ";
	main_menu_frame1[8] =  "             113     11311111176111112  11111176   113   1111111311111112              ";
	main_menu_frame1[9] =  "             113     11311755112117556  11755112   113   1175511345555113              ";
	main_menu_frame1[10] = "             111111121131111117611111112113  113   113   113  11311111113              ";
	main_menu_frame1[11] = "             455555564564555556 45555556456  456   456   456  45645555556              ";
	main_menu_frame1[12] = "                                                                                       ";
	main_menu_frame1[13] = "                             8 Start                                                   ";
	main_menu_frame1[14] = "	                             Controls                                                 ";

	main_menu_frame2[0] =  "112     111112 1111112 112   1121111112 1121112   112111111112112  112 1111112 11111112";
	main_menu_frame2[1] =  "113    11755112117551124112 11761175511211311112  113455117556113  11311755511211755556";
	main_menu_frame2[2] =  "113    1111111311111176 4111176 11111176113117112 113   113   11111113113   11311111112";
	main_menu_frame2[3] =  "113    1175511311755112  41176  117551121131134112113   113   11755113113   11345555113";
	main_menu_frame2[4] =  "1111112113  11311111176   113   113  113113113 411113   113   113  11341111117611111113";
	main_menu_frame2[5] =  "4555556456  4564555556    456   456  456456456  45556   456   456  456 4555556 45555556";
	main_menu_frame2[6] =  "             112     1121111112 111111121111112 111111112 111112 11111112              ";
	main_menu_frame2[7] =  "             113     1131175511211755556117551124551175561175511211755556              ";
	main_menu_frame2[8] =  "             113     11311111176111112  11111176   113   1111111311111112              ";
	main_menu_frame2[9] =  "             113     11311755112117556  11755112   113   1175511345555113              ";
	main_menu_frame2[10] = "             111111121131111117611111112113  113   113   113  11311111113              ";
	main_menu_frame2[11] = "             455555564564555556 45555556456  456   456   456  45645555556              ";
	main_menu_frame2[12] = "                                                                                       ";
	main_menu_frame2[13] = "                               Start                                                   ";
	main_menu_frame2[14] = "	                           8 Controls                                                 ";

	COORD x;

	if (main_menu_1 == true)
	{
		for (int i = 0; i < 15; ++i)
		{
			for (int a = 0; a < 87; ++a)
			{
				x.X = a;
				x.Y = i + 1;
				currentchar = main_menu_frame1[i][a];
				switch (currentchar)
				{
				case('1'):
					currentchar = 219;
					break;
				case('2'):
					currentchar = 187;
					break;
				case('3'):
					currentchar = 186;
					break;
				case('4'):
					currentchar = 200;
					break;
				case('5'):
					currentchar = 205;
					break;
				case('6'):
					currentchar = 188;
					break;
				case('7'):
					currentchar = 201;
					break;
				case('8'):
					currentchar = 62;
					break;
				}
				g_Console.writeToBuffer(x, currentchar, 0x1A);
			}

		}
	}
	if (main_menu_2 == true)
	{
		for (int i = 0; i < 15; ++i)
		{
			for (int a = 0; a < 87; ++a)
			{
				x.X = a;
				x.Y = i + 1;
				currentchar = main_menu_frame2[i][a];
				switch (currentchar)
				{
				case('1'):
					currentchar = 219;
					break;
				case('2'):
					currentchar = 187;
					break;
				case('3'):
					currentchar = 186;
					break;
				case('4'):
					currentchar = 200;
					break;
				case('5'):
					currentchar = 205;
					break;
				case('6'):
					currentchar = 188;
					break;
				case('7'):
					currentchar = 201;
					break;
				case('8'):
					currentchar = 62;
					break;
				}
				g_Console.writeToBuffer(x, currentchar, 0x1A);
			}

		}
	}
}

void control_screen()
{
	COORD x;
	char currentchar;
	string controlscreen[15];

	controlscreen[0] = "                                                                                         ";
	controlscreen[1] = "                                                                                         ";
	controlscreen[2] = "                                                                                         ";
	controlscreen[3] = "                                   MOVING UP = UP ARROW KEY                              ";
	controlscreen[4] = "                                 MOVING DOWN = DOWN ARROW KEY                            ";
	controlscreen[5] = "                                 MOVING LEFT = LEFT ARROW KEY                            ";
	controlscreen[6] = "                                MOVING RIGHT = RIGHT ARROW KEY                           ";
	controlscreen[7] = "                                   Selecting = SPACE KEY                                 ";
	controlscreen[8] = "                                                                                         ";
	controlscreen[9] = "                                    GAMEPLAY legend:                                     ";
	controlscreen[10] = "                                         K - KEY                                         ";
	controlscreen[11] = "                                       M - MONSTERS                                      ";
	controlscreen[12] = "                                       O - Endpoint                                      ";
	controlscreen[13] = "                                                                                         ";
	controlscreen[14] = "  GO BACK - SPACE KEY                                                                    ";
	for (int i = 0; i < 15; ++i)
	{
		for (int a = 0; a < 87; ++a)
		{
			x.X = a;
			x.Y = i + 1;
			currentchar = controlscreen[i][a];
			g_Console.writeToBuffer(x, currentchar, 0x1A);
		}
	}
}

void main_menu_option()
{
	bool bSomethingHappened = false;
	if (g_dBounceTime > g_dElapsedTime)
	{
		return;
	}


	if (main_menu_1 == true)
	{
		if (g_abKeyPressed[K_DOWN])
		{
			main_menu_1 = false;
			main_menu_2 = true;
			bSomethingHappened = true;
		}
		if (g_abKeyPressed[K_SPACE])
		{
			g_eGameState = S_GAME;
			bSomethingHappened = true;
		}
	}
	if (main_menu_2 == true)
	{
		if (g_abKeyPressed[K_UP])
		{
			main_menu_1 = true;
			main_menu_2 = false;
			bSomethingHappened = true;
		}
		if (g_abKeyPressed[K_SPACE])
		{
			g_eGameState = S_CONTROLS;
			bSomethingHappened = true;
		}
	}

	if (bSomethingHappened)
	{
		// set the bounce time to some time in the future to prevent accidental triggers
		g_dBounceTime = g_dElapsedTime + 0.125; // 125ms should be enough
	}
}

void control_screen_back()
{
	bool bSomethingHappened = false;
	if (g_dBounceTime > g_dElapsedTime)
	{
		return;
	}

	if (g_abKeyPressed[K_SPACE])
	{
		g_eGameState = S_SPLASHSCREEN;
		bSomethingHappened = true;
	}

	if (bSomethingHappened)
	{
		// set the bounce time to some time in the future to prevent accidental triggers
		g_dBounceTime = g_dElapsedTime + 0.125; // 125ms should be enough
	}
}

void health() //Do this in the weekend
{
	//If the player loses, then bool(isdead) will be true
	//The player will then lose 1 healthpoint, and then the bool will then return to being false
	if (isdead == true)
	{
		healthpoints--;
		isdead = false;
	}

	//Should the player's health turn to 0, the game will end, leading to the end screen
	if (healthpoints == 0)
	{
		g_eGameState = S_DEATH;
	}
}

void scoresystem() // Do this in the weekend
{
	if (killmob == true) //When a mob is killed, the bool killmob becomes true, then the score increasese by the health the player has left
	{
		score++;
		score += healthpoints;
		killmob = false;
	}
}

void pause_select()
{
	bool bSomethingHappened = false;
	if (g_dBounceTime > g_dElapsedTime)
	{
		return;
	}

	if (pause_1 == true)
	{
		if (g_abKeyPressed[K_DOWN])
		{
			pause_1 = false;
			pause_2 = true;
			pause_3 = false;
			bSomethingHappened = true;
		}
		if (g_abKeyPressed[K_SPACE])
		{
			g_eGameState = S_GAME;
			bSomethingHappened = true;
		}
	}
	if (pause_2 == true)
	{
		if (g_abKeyPressed[K_UP])
		{
			pause_1 = true;
			pause_2 = false;
			pause_3 = false;
			bSomethingHappened = true;
		}
		if (g_abKeyPressed[K_DOWN])
		{
			pause_1 = false;
			pause_2 = false;
			pause_3 = true;
			bSomethingHappened = true;
		}
		if (g_abKeyPressed[K_SPACE])
		{
			g_eGameState = S_SPLASHSCREEN;
			bSomethingHappened = true;
		}
	}
	if (pause_3 == true)
	{
		if (g_abKeyPressed[K_UP])
		{
			pause_1 = false;
			pause_2 = true;
			pause_3 = false;
			bSomethingHappened = true;
		}
		if (g_abKeyPressed[K_SPACE])
		{
			g_bQuitGame = true;
			bSomethingHappened = true;
		}
	}

	if (bSomethingHappened)
	{
		// set the bounce time to some time in the future to prevent accidental triggers
		g_dBounceTime = g_dElapsedTime + 0.125; // 125ms should be enough
	}
}

void pause_screen()
{
	COORD x;
	char currentchar;
	string pause_screen_1[10];
	string pause_screen_2[10];
	string pause_screen_3[10];

	pause_screen_1[0] = "                      ________________________________________                         ";
	pause_screen_1[1] = "                     /                                        1                        ";
	pause_screen_1[2] = "                    |                                          |                       ";
	pause_screen_1[3] = "                    |                 PAUSE                    |                       ";
	pause_screen_1[4] = "                    |                                          |                       ";
	pause_screen_1[5] = "                    |              2 Continue                  |                       ";
	pause_screen_1[6] = "                    |                Main Menu                 |                       ";
	pause_screen_1[7] = "                    |                Exit Game                 |                       ";
	pause_screen_1[8] = "                    |                                          |                       ";
	pause_screen_1[9] = "                     1________________________________________/                        ";

	pause_screen_2[0] = "                      ________________________________________                         ";
	pause_screen_2[1] = "                     /                                        1                        ";
	pause_screen_2[2] = "                    |                                          |                       ";
	pause_screen_2[3] = "                    |                 PAUSE                    |                       ";
	pause_screen_2[4] = "                    |                                          |                       ";
	pause_screen_2[5] = "                    |                Continue                  |                       ";
	pause_screen_2[6] = "                    |              2 Main Menu                 |                       ";
	pause_screen_2[7] = "                    |                Exit Game                 |                       ";
	pause_screen_2[8] = "                    |                                          |                       ";
	pause_screen_2[9] = "                     1________________________________________/                        ";

	pause_screen_3[0] = "                      ________________________________________                         ";
	pause_screen_3[1] = "                     /                                        1                        ";
	pause_screen_3[2] = "                    |                                          |                       ";
	pause_screen_3[3] = "                    |                 PAUSE                    |                       ";
	pause_screen_3[4] = "                    |                                          |                       ";
	pause_screen_3[5] = "                    |                Continue                  |                       ";
	pause_screen_3[6] = "                    |                Main Menu                 |                       ";
	pause_screen_3[7] = "                    |              2 Exit Game                 |                       ";
	pause_screen_3[8] = "                    |                                          |                       ";
	pause_screen_3[9] = "                     1________________________________________/                        ";

	if (pause_1 == true)
	{
		for (int i = 0; i < 10; ++i)
		{
			for (int a = 0; a < 87; ++a)
			{
				x.X = a;
				x.Y = i + 1;
				currentchar = pause_screen_1[i][a];
				switch(currentchar)
				{
				case('1'):
					currentchar = 92;
					break;
				case('2'):
					currentchar = 62;
					break;
				}
				g_Console.writeToBuffer(x, currentchar, 0x1A);
			}
		}
	}
	if (pause_2 == true)
	{
		for (int i = 0; i < 10; ++i)
		{
			for (int a = 0; a < 87; ++a)
			{
				x.X = a;
				x.Y = i + 1;
				currentchar = pause_screen_2[i][a];
				switch (currentchar)
				{
				case('1'):
					currentchar = 92;
					break;
				case('2'):
					currentchar = 62;
					break;
				}
				g_Console.writeToBuffer(x, currentchar, 0x1A);
			}
		}
	}
	if (pause_3 == true)
	{
		for (int i = 0; i < 10; ++i)
		{
			for (int a = 0; a < 87; ++a)
			{
				x.X = a;
				x.Y = i + 1;
				currentchar = pause_screen_3[i][a];
				switch (currentchar)
				{
				case('1'):
					currentchar = 92;
					break;
				case('2'):
					currentchar = 62;
					break;
				}
				g_Console.writeToBuffer(x, currentchar, 0x1A);
			}
		}
	}

}

string whichText(string *output, bool *BoolArray)
{
	srand(time(nullptr));
	bool done = true;
	while (done)
	{
		int a = rand() % 18 + 1;
		if (bArray[a - 1])
		{
			switch (a)
			{
			case 1:
			{
				*output += Monster1.monsterName;
				*output += ' ';
				*output += Monster1.monsterQn;
				*output += ' ';
				*output += Monster1.ans1;
				*output += ' ';
				*output += Monster1.ans2;
				*output += ' ';
				*output += Monster1.ans3;

			}
			break;
			case 2:
				*output += Monster2.monsterName;
				*output += ' ';
				*output += Monster2.monsterQn;
				*output += ' ';
				*output += Monster2.ans1;
				*output += ' ';
				*output += Monster2.ans2;
				*output += ' ';
				*output += Monster2.ans3;
				break;
			case 3:
				*output += Monster3.monsterName;
				*output += ' ';
				*output += Monster3.monsterQn;
				*output += ' ';
				*output += Monster3.ans1;
				*output += ' ';
				*output += Monster3.ans2;
				*output += ' ';
				*output += Monster3.ans3;
				break;
			case 4:
				*output += Monster4.monsterName;
				*output += ' ';
				*output += Monster4.monsterQn;
				*output += ' ';
				*output += Monster4.ans1;
				*output += ' ';
				*output += Monster4.ans2;
				*output += ' ';
				*output += Monster4.ans3;
				break;
			case 5:
				*output += Monster5.monsterName;
				*output += ' ';
				*output += Monster5.monsterQn;
				*output += ' ';
				*output += Monster5.ans1;
				*output += ' ';
				*output += Monster5.ans2;
				*output += ' ';
				*output += Monster5.ans3;
				break;
			case 6:
				*output += Monster6.monsterName;
				*output += ' ';
				*output += Monster6.monsterQn;
				*output += ' ';
				*output += Monster6.ans1;
				*output += ' ';
				*output += Monster6.ans2;
				*output += ' ';
				*output += Monster6.ans3;
				break;
			case 7:
				*output += Monster7.monsterName;
				*output += ' ';
				*output += Monster7.monsterQn;
				*output += ' ';
				*output += Monster7.ans1;
				*output += ' ';
				*output += Monster7.ans2;
				*output += ' ';
				*output += Monster7.ans3;
				break;
			case 8:
				*output += Monster8.monsterName;
				*output += ' ';
				*output += Monster8.monsterQn;
				*output += ' ';
				*output += Monster8.ans1;
				*output += ' ';
				*output += Monster8.ans2;
				*output += ' ';
				*output += Monster8.ans3;
				break;
			case 9:
				*output += Monster9.monsterName;
				*output += ' ';
				*output += Monster9.monsterQn;
				*output += ' ';
				*output += Monster9.ans1;
				*output += ' ';
				*output += Monster9.ans2;
				*output += ' ';
				*output += Monster9.ans3;
				break;
			case 10:
				*output += Monster10.monsterName;
				*output += ' ';
				*output += Monster10.monsterQn;
				*output += ' ';
				*output += Monster10.ans1;
				*output += ' ';
				*output += Monster10.ans2;
				*output += ' ';
				*output += Monster10.ans3;
				break;
			case 11:
				*output += Monster11.monsterName;
				*output += ' ';
				*output += Monster11.monsterQn;
				*output += ' ';
				*output += Monster11.ans1;
				*output += ' ';
				*output += Monster11.ans2;
				*output += ' ';
				*output += Monster11.ans3;
				break;
			case 12:
				*output += Monster12.monsterName;
				*output += ' ';
				*output += Monster12.monsterQn;
				*output += ' ';
				*output += Monster12.ans1;
				*output += ' ';
				*output += Monster12.ans2;
				*output += ' ';
				*output += Monster12.ans3;
				break;
			case 13:
				*output += Monster13.monsterName;
				*output += ' ';
				*output += Monster13.monsterQn;
				*output += ' ';
				*output += Monster13.ans1;
				*output += ' ';
				*output += Monster13.ans2;
				*output += ' ';
				*output += Monster13.ans3;
				break;
			case 14:
				*output += Monster14.monsterName;
				*output += ' ';
				*output += Monster14.monsterQn;
				*output += ' ';
				*output += Monster14.ans1;
				*output += ' ';
				*output += Monster14.ans2;
				*output += ' ';
				*output += Monster14.ans3;
				break;
			case 15:
				*output += Monster15.monsterName;
				*output += ' ';
				*output += Monster15.monsterQn;
				*output += ' ';
				*output += Monster15.ans1;
				*output += ' ';
				*output += Monster15.ans2;
				*output += ' ';
				*output += Monster15.ans3;
				break;
			case 16:
				*output += Monster16.monsterName;
				*output += ' ';
				*output += Monster16.monsterQn;
				*output += ' ';
				*output += Monster16.ans1;
				*output += ' ';
				*output += Monster16.ans2;
				*output += ' ';
				*output += Monster16.ans3;
				break;
			case 17:
				*output += Monster17.monsterName;
				*output += ' ';
				*output += Monster17.monsterQn;
				*output += ' ';
				*output += Monster17.ans1;
				*output += ' ';
				*output += Monster17.ans2;
				*output += ' ';
				*output += Monster17.ans3;
				break;
			case 18:
				*output += Monster18.monsterName;
				*output += ' ';
				*output += Monster18.monsterQn;
				*output += ' ';
				*output += Monster18.ans1;
				*output += ' ';
				*output += Monster18.ans2;
				*output += ' ';
				*output += Monster18.ans3;
				break;
			default:
				break;
			}

			bArray[a - 1] = false;
		}
		done = false;
	}
	return *output;
}

/*
what happens when the player runs into an entity?
the game checks which entity they ran into and render the corresponding text
eg: run into mob1
check that player run into mob1
access text relating to mob1
render text of mob1
after finish clean textbox
*/



//when enter combat
//gamestate change to combat
//frame freeze
//run function for anser input
//take in user input

