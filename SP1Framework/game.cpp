// This is the main file for the game logic and function
//
//
#include "game.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <ctime>
#include <random>

using namespace std;

// for mobs
ifstream initMobs("MobsFinalUpdated.txt");

char map[30][101];
bool moveAllow = true;

int lvlcleared = 1;
int changeinlvl = 1;

double  g_dElapsedTime;
double  g_dDeltaTime;
bool    g_abKeyPressed[K_COUNT];
/*
void playmusic(gamemusic.wav, NULL, SND_ASYNC | SND_LOOP)
{
	

}
*/
int healthpoints = 3;				// number of lives player has
int score = 0;						// player score
int keycount;
bool isdead = false;				// bool when player loses to the mob once
bool killmob = false;				// bool for when player kills the mob
bool main_menu_1 = true;			// to check if player is choosing the start option
bool main_menu_2 = false;			// to check if player is choosing the controls option
bool main_menu_3 = false;
bool pause_1 = true;				// to check if player is choosing continue
bool pause_2 = false;				// to check if player is choosing to go to main menu
bool pause_3 = false;				// to check if player is choosing to exit game
bool difficulty_option = true;
bool easy = true;
bool medium = false;
bool hard = false;
struct monstatus monster[7];
// Game specific variables here
SGameChar g_sChar;

double  g_dBounceTime; // this is to prevent key bouncing, so we won't trigger keypresses more than once
double  g_dBounceTime2;

// Console object
EGAMESTATES g_eGameState;

Console g_Console(101, 60, "                                                             Labyrinthos Libertas");


//--------------------------------------------------------------
// Purpose  : Initialisation function
//            Initialize variables, allocate memory, load data from file, etc. 
//            This is called once before entering into your main loop
// Input    : void
// *output   : void
//--------------------------------------------------------------
void init( void )
{
	for (int i = 0; i < sizeof(bArray); i++)  // initialise all the memory to be true for the mobs' text
	{
		bArray[i] = true;
	}
	//initialise all the mob info
	initMobText(&mob1, &initMobs);
	initMobText(&mob2, &initMobs);
	initMobText(&mob3, &initMobs);
	initMobText(&mob4, &initMobs);
	initMobText(&mob5, &initMobs);
	initMobText(&mob6, &initMobs);
	initMobText(&mob7, &initMobs);
	initMobText(&mob8, &initMobs);
	initMobText(&mob9, &initMobs);
	initMobText(&mob10, &initMobs);
	initMobText(&mob11, &initMobs);
	initMobText(&mob12, &initMobs);
	initMobText(&mob13, &initMobs);
	initMobText(&mob14, &initMobs);
	initMobText(&mob15, &initMobs);
	initMobText(&mob16, &initMobs);
	initMobText(&mob17, &initMobs);
	initMobText(&mob18, &initMobs);
	initMobText(&mob19, &initMobs);
	initMobText(&mob20, &initMobs);
	initMobText(&mob21, &initMobs);
	initMobText(&mob22, &initMobs);
	initMobText(&mob23, &initMobs);
	initMobText(&mob24, &initMobs);
	initMobText(&mob25, &initMobs);
	initMobText(&mob26, &initMobs);
	initMobText(&mob27, &initMobs);
	initMobText(&mob28, &initMobs);
	initMobText(&mob29, &initMobs);
	initMobText(&mob30, &initMobs);
	initMobText(&mob31, &initMobs);
	initMobText(&mob32, &initMobs);
	initMobText(&mob33, &initMobs);
	initMobText(&mob34, &initMobs);
	initMobText(&mob35, &initMobs);
	initMobText(&mob36, &initMobs);
	initMobText(&mob37, &initMobs);
	initMobText(&mob38, &initMobs);
	initMobText(&mob39, &initMobs);
	initMobText(&mob40, &initMobs);
	initMobText(&mob41, &initMobs);
	initMobText(&mob42, &initMobs);
	// initialise answers for mobs
	

    // Set precision for floating point *output
    g_dElapsedTime = 0.0;
    g_dBounceTime = 0.0;
	g_dBounceTime2 = 0.0;

    // sets the initial state for the game
    g_eGameState = S_SPLASHSCREEN;

    g_sChar.m_cLocation.X = g_Console.getConsoleSize().X / 2;
    g_sChar.m_cLocation.Y = 5;
    g_sChar.m_bActive = true;
    // sets the width, height and the font name to use in the console
    g_Console.setConsoleFont(16, 0, L"Consolas");

	MusicInit();
	MusicPlay("gamemusic", "repeat");

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
	case S_SPLASHSCREEN: main_menu_option(); // game logic for the splash screen
            break;
		case S_COMBAT:
			duration(&g_eGameState, dt);
			combatlogic();
			gameplay();
			break;
		case S_COMBATAFTERMATH:
			stopPrintingCOrW(dt);
			gameplay();
			break;
        case S_GAME: totalTime = 0; // resets the combat timer
			timeForCOrW = 0;
			gameplay(); // gameplay logic when we are in the game
            break;
		case S_DEATH: game_over_option();
			break;
		case S_CONTROLS: control_screen_back();
			break;
		case S_PAUSE: pause_select();
			break;
		case S_DIFFICULTY: difficulty_choose();
			break;
		case S_WIN: win_options();
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
	case S_SPLASHSCREEN: main_menu();
            break;
        case S_GAME: renderGame();
            break;
		case S_COMBATAFTERMATH:	renderGame();
			printCOrW();
			break;
		case S_COMBAT: renderGame();
			COMBAT();
			break;
		case S_CONTROLS: control_screen();
			break;
		case S_DEATH: game_over();
			break;
		case S_PAUSE: pause_screen();
			break;
		case S_DIFFICULTY: difficulty_screen();
			break;
		case S_WIN: win_screen();
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
    processUserInput();// checks if you should change states or do something else with the game, e.g. pause, exit
	if (g_eGameState == S_GAME)
	{
		moveCharacter();    // moves the character, collision detection, physics, etc
	}                   // sound can be played here too.
    processUserInput(); // checks if you should change states or do something else with the game, e.g. pause, exit
                        // sound can be played here too.
	health();
	movemobs();
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
	if (moveAllow)
	{
		if ((g_abKeyPressed[K_UP]) && (collision(map, (g_sChar.m_cLocation.Y - 1), g_sChar.m_cLocation.X) != true))
		{
			g_sChar.m_cLocation.Y--;
			if (touchmonster(g_sChar, monster) == true)
			{
				moveAllow = false;
				g_eGameState = S_COMBAT;
				map[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] = ' ';
			}
			else if (touchkey(map, g_sChar.m_cLocation.Y, g_sChar.m_cLocation.X) == true)
			{

				//run text for key
				c.Y = g_sChar.m_cLocation.Y;
				c.X = g_sChar.m_cLocation.X;
				//run text for key
				map[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] = ' ';
				keycount--;
			}
			else if (touchend(map, g_sChar.m_cLocation.Y, g_sChar.m_cLocation.X) == true)
			{
				if (keycount == 0)
				{
					//run text for end door password, if correct, do lvlcleared++ to change lvl on next render, reset pos of player
					lvlcleared++;
					g_sChar.m_cLocation.X = g_Console.getConsoleSize().X / 2;
					g_sChar.m_cLocation.Y = 5;
				}
			}
			bSomethingHappened = true;

		}
		if ((g_abKeyPressed[K_LEFT]) && (collision(map, g_sChar.m_cLocation.Y, (g_sChar.m_cLocation.X - 1)) != true))//performs movement if keystroke is pressed and if there is no wall in the direction of travel
		{
			g_sChar.m_cLocation.X--;
			if (touchmonster(g_sChar, monster) == true)
			{
				moveAllow = false;
				g_eGameState = S_COMBAT;
				map[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] = ' ';
			}
			else if (touchkey(map, g_sChar.m_cLocation.Y, g_sChar.m_cLocation.X) == true)
			{
				c.Y = g_sChar.m_cLocation.Y;
				c.X = g_sChar.m_cLocation.X;
				//run text for key
				map[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] = ' ';
				keycount--;
			}
			else if (touchend(map, g_sChar.m_cLocation.Y, g_sChar.m_cLocation.X) == true)
			{
				if (keycount == 0)
				{
					//run text for end door password, if correct, do lvlcleared++ to change lvl on next render, reset pos of player
					lvlcleared++;
					g_sChar.m_cLocation.X = g_Console.getConsoleSize().X / 2;
					g_sChar.m_cLocation.Y = 5;
					keycount = 0;
				}
			}
			bSomethingHappened = true;
		}
		if ((g_abKeyPressed[K_DOWN]) && (collision(map, (g_sChar.m_cLocation.Y + 1), g_sChar.m_cLocation.X) != true))
		{
			g_sChar.m_cLocation.Y++;

			if (touchmonster(g_sChar, monster) == true)
			{
				moveAllow = false;
				g_eGameState = S_COMBAT;
				map[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] = ' ';
			}
			else if (touchkey(map, g_sChar.m_cLocation.Y, g_sChar.m_cLocation.X) == true)
			{
				c.Y = g_sChar.m_cLocation.Y;
				c.X = g_sChar.m_cLocation.X;
				//run text for key
				map[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] = ' ';
				keycount--;
			}
			else if (touchend(map, g_sChar.m_cLocation.Y, g_sChar.m_cLocation.X) == true)
			{
				if (keycount == 0)
				{
					//run text for end door password, if correct, do lvlcleared++ to change lvl on next render, reset pos of player
					lvlcleared++;
					g_sChar.m_cLocation.X = g_Console.getConsoleSize().X / 2;
					g_sChar.m_cLocation.Y = 5;
					keycount = 0;
				}
			}
			bSomethingHappened = true;

		}
		if ((g_abKeyPressed[K_RIGHT]) && (collision(map, g_sChar.m_cLocation.Y, (g_sChar.m_cLocation.X + 1)) != true))
		{
			g_sChar.m_cLocation.X++;
			if (touchmonster(g_sChar, monster) == true)
			{
				moveAllow = false;
				g_eGameState = S_COMBAT;
				map[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] = ' ';
			}
			else if (touchkey(map, g_sChar.m_cLocation.Y, g_sChar.m_cLocation.X) == true)
			{
				c.Y = g_sChar.m_cLocation.Y;
				c.X = g_sChar.m_cLocation.X;
				//run text for key
				map[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] = ' ';
				keycount--;
			}
			else if (touchend(map, g_sChar.m_cLocation.Y, g_sChar.m_cLocation.X) == true)
			{
				if (keycount == 0)
				{
					//run text for end door password, if correct, do lvlcleared++ to change lvl on next render, reset pos of player
					lvlcleared++;
					g_sChar.m_cLocation.X = g_Console.getConsoleSize().X / 2;
					g_sChar.m_cLocation.Y = 5;
					keycount = 0;
				}
			}
			bSomethingHappened = true;
		}
	}

	if (bSomethingHappened)
	{
		// set the bounce time to some time in the future to prevent accidental triggers
		g_dBounceTime = g_dElapsedTime + 0.025; // 125ms should be enough
	}

}
void processUserInput()
{
    // quits the game if player hits the escape key
    if (g_abKeyPressed[K_ESCAPE])
		g_eGameState = S_PAUSE;
}

void clearScreen()
{
    // Clears the buffer with this colour attribute
    g_Console.clearBuffer(0x1F);
}

void renderGame()
{
    renderMap();        // renders the map to the buffer first
    renderCharacter();  // renders the character into the buffer
}

void renderMap()
{
    //Set up sample colours, and output shadings
    const WORD colors[] = {
        0x06, 0x2B, 0x3C, 0x4D, 0x5E, 0x6F,
        0xA1, 0xB2, 0xC3, 0xD4, 0xE5, 0xF6
    };
    COORD c;
	colour(colors[0]);

	
	string healthtext = "Health : ";
	COORD a;
	char currentchar;
	currentchar = 3;
	a.X = 1;
	a.Y = 32;
	for (int i = 0; i < 9; ++i)
	{
		g_Console.writeToBuffer(a, healthtext[i], 0x1F);
		a.X++;
	}
	for (int i = 0; i < healthpoints; ++i)
	{
		g_Console.writeToBuffer(a, currentchar, 0x1C);
		a.X++;
		g_Console.writeToBuffer(a, ' ', 0x1F);
		a.X++;
	}

	
	a.X = 18;
	a.Y = 32;
	string keystext = "Keys to find : ";

	unsigned char currentchar2 = 235;
	for (int i = 0; i < 15; ++i)
	{
		g_Console.writeToBuffer(a, keystext[i], 0x1F);
		a.X++;
	}
	for (int i = 0; i < keycount /*keystr.length()*/; ++i)
	{
		g_Console.writeToBuffer(a, currentchar2, 0x1F);
		a.X++;
		g_Console.writeToBuffer(a, ' ', 0x1F);
		a.X++;
	}
	
	colour(colors[0]);
	string rows;
	string cols;
	string keys;
	string filename;
	int y;
	int x;

	switch (lvlcleared)
	{
	case 1:
		filename += "lvl7.txt";
		break;
	case 2:
		filename += "lvl2.txt";
		break;
	case 3:
		filename += "lvl3.txt";
		break;
	case 4:
		filename += "lvl4.txt";
		break;
	case 5:
		filename += "lvl5.txt";
		break;
	case 6:
		filename += "lvl6.txt";
		break;
	case 7:
		g_eGameState = S_WIN;
		break;
	}


	if (lvlcleared == changeinlvl && lvlcleared < 7)
	{
		ifstream currentlvl;
		currentlvl.open(filename);
		getline(currentlvl, cols);
		getline(currentlvl, rows);
		getline(currentlvl, keys);
		y = stoi(rows);
		x = stoi(cols);
		keycount = stoi(keys);

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
					break;
				case'k':
					map[i][j] = 'k';
					break;
				case'o':
					map[i][j] = 'o';
					break;
				case ' ':
					map[i][j] = ' ';	
					break;				
				default:
					break;

				}
			}
		}
		changeinlvl++;
		currentlvl.close();

		int xPos;
		int yPos;
		int repcount = 0;
		srand((unsigned int)time(nullptr));

		while (repcount != 6)
		{
			xPos = (rand() % 102 + 1) + rand() % 4;
			yPos = (rand() % 31 + 1) + rand() % 3;

			if (map[(yPos)][(xPos)] == ' ')
			{
				monster[repcount].location.X = xPos;
				monster[repcount].location.Y = yPos;
				monster[repcount].alive = true;
			}
			else
			{
				continue;
			}

			repcount++;
		}
	}
	else
	{
		for (int i = 0; i < 30; ++i)
		{
			for (int j = 0; j < 101; ++j)
			{
				c.X = j;
				c.Y = i;
				if (map[i][j] == ' ')
				{
					g_Console.writeToBuffer(c, map[i][j], 0xFF);
				}
				if (map[i][j] == 'k')
				{
					g_Console.writeToBuffer(c, (char)235, 0x0E);
				}
				if (map[i][j] == 'o')
				{
					g_Console.writeToBuffer(c, map[i][j], 0x0B);
				}
			}
		}
	}
	
	for (int i = 0; i < 6; i++)
	{
		if (monster[i].alive == true)
		{
			g_Console.writeToBuffer(monster[i].location, (char)004, 0x0C);
		}
	}
}

void renderCharacter()
{
    // Draw the location of the character
    WORD charColor = 0x0C;//default color of character
    if (g_sChar.m_bActive)//if spacebar is pressed, change the color of character
    {
        charColor = 0x0A;
    }
    g_Console.writeToBuffer(g_sChar.m_cLocation, 'X', charColor);//send character printing details to the buffer
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

void pause_screen()
{
	COORD c;
	string rows;
	string cols;
	string filename;
	int y;
	int x;

	filename += "pause_screen.txt";

	ifstream pausescreen;
	pausescreen.open(filename);
	getline(pausescreen, cols);
	getline(pausescreen, rows);
	y = stoi(rows);
	x = stoi(cols);

	for (int i = 0; i < y; ++i)
	{
		string currentrow;
		char currentchar;
		getline(pausescreen, currentrow);
		for (int j = 0; j < x; ++j)
		{
			currentchar = currentrow[j];

			c.X = j;
			c.Y = i + 1;

			switch (currentchar)
			{
			case('1'):
				currentchar = 92;
				break;
			}
			g_Console.writeToBuffer(c, currentchar, 0x1F);
		}
	}

	COORD b;
	char currentchar2 = 62;

	if (pause_1 == true)
	{
		b.Y = 6;
		b.X = 35;
	}
	if (pause_2 == true)
	{
		b.Y = 7;
		b.X = 35;
	}
	if (pause_3 == true)
	{
		b.Y = 8;
		b.X = 35;
	}

	g_Console.writeToBuffer(b, currentchar2, 0x1F);
}

void control_screen()
{
	COORD c;
	string rows;
	string cols;
	string filename;
	int y;
	int x;

	filename += "Controls.txt";

	ifstream controlsmenu;
	controlsmenu.open(filename);
	getline(controlsmenu, cols);
	getline(controlsmenu, rows);
	y = stoi(rows);
	x = stoi(cols);

	for (int i = 0; i < y; ++i)
	{
		string currentrow;
		char currentchar;
		getline(controlsmenu, currentrow);
		for (int j = 0; j < x; ++j)
		{
			currentchar = currentrow[j];

			c.X = j;
			c.Y = i;
			g_Console.writeToBuffer(c, currentchar, 0x1F);
		}
	}
}

void main_menu()
{
	COORD c;
	string rows;
	string cols;
	string filename;
	int y;
	int x;

	filename += "main_menu_frame.txt";

	ifstream mainmenu;
	mainmenu.open(filename);
	getline(mainmenu, cols);
	getline(mainmenu, rows);
	y = stoi(rows);
	x = stoi(cols);

	for (int i = 0; i < y; ++i)
	{
		string currentrow;
		unsigned char currentchar;
		getline(mainmenu, currentrow);
		for (int j = 0; j < x; ++j)
		{
			currentchar = currentrow[j];

			c.X = j;
			c.Y = i + 1;

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
			}
			g_Console.writeToBuffer(c, currentchar, 0x1F);
		}
	}
	mainmenu.close();

	string difficultystr = "                                       Difficulty                                      ";
	
	if (difficulty_option == true)
	{
		c.Y = 16;
		for (int i = 0; i < 87; ++i)
		{
			c.X = i;
			g_Console.writeToBuffer(c, difficultystr[i], 0x1F);
		}
	}
	char currentchar2 = 62;
	COORD b;
	if (main_menu_1 == true)
	{
		b.Y = 14;
		b.X = 39;
	}
	if (main_menu_2 == true)
	{
		b.Y = 15;
		b.X = 38;
	}
	if (main_menu_3 == true)
	{
		b.Y = 16;
		b.X = 37;
	}

	g_Console.writeToBuffer(b, currentchar2, 0x1F);
}

void game_over()
{
	COORD c;
	string rows;
	string cols;
	string filename;
	int y;
	int x;

	filename += "game_over_screen.txt";

	ifstream gameover;
	gameover.open(filename);
	getline(gameover, cols);
	getline(gameover, rows);
	y = stoi(rows);
	x = stoi(cols);

	for (int i = 0; i < y; ++i)
	{
		string currentrow;
		char currentchar;
		getline(gameover, currentrow);
		for (int j = 0; j < x; ++j)
		{
			currentchar = currentrow[j];

			c.X = j + 1;
			c.Y = i + 1;

			switch (currentchar)
			{
			case('1'):
				currentchar = 92;
				break;
			}
			g_Console.writeToBuffer(c, currentchar, 0x1F);
		}
	}
	gameover.close();
}

void difficulty_screen()
{
	COORD c;
	string rows;
	string cols;
	string filename;
	int y;
	int x;

	filename += "difficulty.txt";

	ifstream difficulty;
	difficulty.open(filename);
	getline(difficulty, cols);
	getline(difficulty, rows);
	y = stoi(rows);
	x = stoi(cols);

	for (int i = 0; i < y; ++i)
	{
		string currentrow;
		char currentchar;
		getline(difficulty, currentrow);
		for (int j = 0; j < x; ++j)
		{
			currentchar = currentrow[j];

			c.X = j;
			c.Y = i + 5;
			g_Console.writeToBuffer(c, currentchar, 0x1F);
		}
	}
	difficulty.close();
	COORD b;
	char currentchar2 = 62;
	b.X = 26;
	if (easy == true)
	{
		b.Y = 7;
	}
	else if (medium == true)
	{
		b.Y = 8;
	}
	else if (hard == true)
	{
		b.Y = 9;
	}

	g_Console.writeToBuffer(b, currentchar2, 0x1F);
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
	else if (main_menu_2 == true)
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
		if (difficulty_option == true)
		{
			if (g_abKeyPressed[K_DOWN])
			{
				main_menu_2 = false;
				main_menu_3 = true;
				bSomethingHappened = true;
			}
		}
	}
	else if (main_menu_3 == true)
	{
		if (g_abKeyPressed[K_UP])
		{
			main_menu_2 = true;
			main_menu_3 = false;
			bSomethingHappened = true;
		}
		if (g_abKeyPressed[K_SPACE])
		{
			g_eGameState = S_DIFFICULTY;
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

void difficulty_choose()
{
	bool bSomethingHappened = false;
	if (g_dBounceTime > g_dElapsedTime)
	{
		return;
	}

	if (easy == true)
	{
		if (g_abKeyPressed[K_DOWN])
		{
			easy = false;
			medium = true;
			hard = false;
			bSomethingHappened = true;
		}
		if (g_abKeyPressed[K_SPACE])
		{
			healthpoints = 3;
			bSomethingHappened = true;
			difficulty_option = false;
			main_menu_1 = true;
			main_menu_3 = false;
			g_eGameState = S_SPLASHSCREEN;
		}
	}
	else if (medium == true)
	{
		if (g_abKeyPressed[K_DOWN])
		{
			medium = false;
			hard = true;
			easy = false;
			bSomethingHappened = true;
		}
		if (g_abKeyPressed[K_UP])
		{
			medium = false; 
			easy = true;
			hard = false;
			bSomethingHappened = true;
		}
		if (g_abKeyPressed[K_SPACE])
		{
			healthpoints = 2;
			bSomethingHappened = true;
			difficulty_option = false;
			main_menu_1 = true;
			main_menu_3 = false;
			g_eGameState = S_SPLASHSCREEN;
		}
	}
	else if (hard == true)
	{
		if (g_abKeyPressed[K_UP])
		{
			medium = true;
			hard = false;
			easy = false;
			bSomethingHappened = true;
		}
		if (g_abKeyPressed[K_SPACE])
		{
			healthpoints = 1;
			bSomethingHappened = true;
			difficulty_option = false;
			main_menu_1 = true;
			main_menu_3 = false;
			g_eGameState = S_SPLASHSCREEN;
		}
	}

	if (bSomethingHappened)
	{
		// set the bounce time to some time in the future to prevent accidental triggers
		g_dBounceTime = g_dElapsedTime + 0.125; // 125ms should be enough
	}
}

void health()
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

void pause_select() // allows players to select between going back to the main menu, continuing, or exit the game
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
	else if (pause_2 == true)
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
			healthpoints = 3;
			lvlcleared = 1;
			changeinlvl = 1;
			difficulty_option = true;
		}
	}
	else if (pause_3 == true)
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



void movemobs() // moves all mobs
{
	bool bSomethingHappened = false;
	for (int i = 0; i < 6; ++i) // to ensure all mobs go through the loop and move
	{
		if (g_dBounceTime2 > g_dElapsedTime) // ensure that mobs also get bouncetime
			return;
		mobmovement(map, i); // moves the mob
		bSomethingHappened = true;
	}

	if (bSomethingHappened)
	{
		// set the bounce time to some time in the future to prevent accidental triggers
		g_dBounceTime2 = g_dElapsedTime + 0.125; // 125ms should be enough
	}
}
//END OF COMBAT RENDERING

void game_over_option() // losers cannot go back into the game. go out immediately 
{
	if (g_abKeyPressed[K_SPACE])
	{
		g_bQuitGame = true;
	}
}

void win_screen() // prints out win screen for winners
{
	COORD c;
	string rows;
	string cols;
	string filename;
	int y;
	int x;

	filename += "win_screen.txt";

	ifstream winscreen;
	winscreen.open(filename);
	getline(winscreen, cols);
	getline(winscreen, rows);
	y = stoi(rows);
	x = stoi(cols);

	for (int i = 0; i < y; ++i)
	{
		string currentrow;
		char currentchar;
		getline(winscreen, currentrow);
		for (int j = 0; j < x; ++j)
		{
			currentchar = currentrow[j];

			c.X = j + 1;
			c.Y = i + 1;

			switch (currentchar)
			{
			case('1'):
				currentchar = 92;
				break;
			}
			g_Console.writeToBuffer(c, currentchar, 0x1F);
		}
	}
	winscreen.close();
}

void win_options() // winners don't have to go through all the torture again
{
	if (g_abKeyPressed[K_SPACE])
	{
		g_bQuitGame = true;
	}
}