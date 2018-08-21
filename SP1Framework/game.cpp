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

char map[15][87];
// for mobs
bool bArray[18]; // bool array for random mob gen so that it doesnt print twice
ifstream initMobs("MobsFinal.txt");
ifstream mobAns("mobAns.txt");
Text mob1;
Text mob2;
Text mob3;
Text mob4;
Text mob5;
Text mob6;
Text mob7;
Text mob8;
Text mob9;
Text mob10;
Text mob11;
Text mob12;
Text mob13;
Text mob14;
Text mob15;
Text mob16;
Text mob17;
Text mob18;

string continueRender;
string mobAnswers;

int ansPasser; // for the answer checker

int g = 0;
int h = 0;
//important
double totalTime = 0;

bool moveAllow = true;
//important

int lvlcleared = 1;
int changeinlvl = 1;

double  g_dElapsedTime;
double  g_dDeltaTime;
bool    g_abKeyPressed[K_COUNT];

bool isdead = false;				// bool when player loses to the mob once
bool killmob = false;				// bool for when player kills the mob
int healthpoints = 3;				// number of lives player has
int score = 0;						// player score
bool main_menu_1 = true;			// to check if player is choosing the start option
bool main_menu_2 = false;			// to check if player is choosing the controls option
bool main_menu_3 = false;
bool pause_1 = true;				// to check if player is choosing continue
bool pause_2 = false;				// to check if player is choosing to go to main menu
bool pause_3 = false;				// to check if player is choosing to exit game
int keycount = 0;
bool difficulty_option = true;
bool difficulty1 = true;
bool difficulty2 = false;

// Game specific variables here
SGameChar   g_sChar;

double  g_dBounceTime; // this is to prevent key bouncing, so we won't trigger keypresses more than once

// Console object
EGAMESTATES g_eGameState;

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
	// initialise answers for mobs
	initAns(&mobAns, &mobAnswers); 

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
		case S_COMBAT: gameplay();
			duration(&g_eGameState, dt);
			break;
        case S_GAME: gameplay(); // gameplay logic when we are in the game
            break;
		case S_DEATH: 
			break;
		case S_CONTROLS: control_screen_back();
			break;
		case S_PAUSE: pause_select();
			break;
		case S_DIFFICULTY:
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
		case S_COMBAT: renderGame();
			COMBAT();
			break;
		case S_CONTROLS: control_screen();
			break;
		case S_DEATH: game_over();
			break;
		case S_PAUSE: pause_screen();
			break;
		case S_DIFFICULTY:
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
	if (moveAllow)
	{


		if ((g_abKeyPressed[K_UP]) && (collision(map, (g_sChar.m_cLocation.Y - 1), g_sChar.m_cLocation.X) != true))
		{
			//Beep(1440, 30);
			g_sChar.m_cLocation.Y--;
			if (touchmonster(map, g_sChar.m_cLocation.Y, g_sChar.m_cLocation.X) == true)
			{
				moveAllow = false;
				g_eGameState = S_COMBAT;
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
				moveAllow = false;
				g_eGameState = S_COMBAT;
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
		if ((g_abKeyPressed[K_DOWN]) && (collision(map, (g_sChar.m_cLocation.Y + 1), g_sChar.m_cLocation.X) != true))
		{
			//Beep(1440, 30);
			g_sChar.m_cLocation.Y++;
			if (touchmonster(map, g_sChar.m_cLocation.Y, g_sChar.m_cLocation.X) == true)
			{
				moveAllow = false;
				g_eGameState = S_COMBAT;
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
		if ((g_abKeyPressed[K_RIGHT]) && (collision(map, g_sChar.m_cLocation.Y, (g_sChar.m_cLocation.X + 1)) != true))
		{
			//Beep(1440, 30);
			g_sChar.m_cLocation.X++;
			if (touchmonster(map, g_sChar.m_cLocation.Y, g_sChar.m_cLocation.X) == true)
			{
				moveAllow = false;
				g_eGameState = S_COMBAT;
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
}

void renderMap()
{
    //Set up sample colours, and output shadings
    const WORD colors[] = {
        0x1A, 0x2B, 0x3C, 0x4D, 0x5E, 0x6F,
        0xA1, 0xB2, 0xC3, 0xD4, 0xE5, 0xF6
    };
    COORD c;
	colour(colors[0]);


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
	//g_Console.writeToBuffer(Text, whichText(&texty, &bArray[18]), colors[0]);

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

void main_menu()
{
	string main_menu_frame1[15];
	string main_menu_frame2[15];
	string main_menu_frame3[15];
	char currentchar;
	string difficulty_line_1, difficulty_line_2;

	main_menu_frame1[0] = "112     111112 1111112 112   1121111112 1121112   112111111112112  112 1111112 11111112";
	main_menu_frame1[1] = "113    11755112117551124112 11761175511211311112  113455117556113  11311755511211755556";
	main_menu_frame1[2] = "113    1111111311111176 4111176 11111176113117112 113   113   11111113113   11311111112";
	main_menu_frame1[3] = "113    1175511311755112  41176  117551121131134112113   113   11755113113   11345555113";
	main_menu_frame1[4] = "1111112113  11311111176   113   113  113113113 411113   113   113  11341111117611111113";
	main_menu_frame1[5] = "4555556456  4564555556    456   456  456456456  45556   456   456  456 4555556 45555556";
	main_menu_frame1[6] = "             112     1121111112 111111121111112 111111112 111112 11111112              ";
	main_menu_frame1[7] = "             113     1131175511211755556117551124551175561175511211755556              ";
	main_menu_frame1[8] = "             113     11311111176111112  11111176   113   1111111311111112              ";
	main_menu_frame1[9] = "             113     11311755112117556  11755112   113   1175511345555113              ";
	main_menu_frame1[10] = "             111111121131111117611111112113  113   113   113  11311111113              ";
	main_menu_frame1[11] = "             455555564564555556 45555556456  456   456   456  45645555556              ";
	main_menu_frame1[12] = "                                                                                       ";
	main_menu_frame1[13] = "                                        8 Start                                        ";
	main_menu_frame1[14] = "                                        Controls                                       ";

	main_menu_frame2[0] = "112     111112 1111112 112   1121111112 1121112   112111111112112  112 1111112 11111112";
	main_menu_frame2[1] = "113    11755112117551124112 11761175511211311112  113455117556113  11311755511211755556";
	main_menu_frame2[2] = "113    1111111311111176 4111176 11111176113117112 113   113   11111113113   11311111112";
	main_menu_frame2[3] = "113    1175511311755112  41176  117551121131134112113   113   11755113113   11345555113";
	main_menu_frame2[4] = "1111112113  11311111176   113   113  113113113 411113   113   113  11341111117611111113";
	main_menu_frame2[5] = "4555556456  4564555556    456   456  456456456  45556   456   456  456 4555556 45555556";
	main_menu_frame2[6] = "             112     1121111112 111111121111112 111111112 111112 11111112              ";
	main_menu_frame2[7] = "             113     1131175511211755556117551124551175561175511211755556              ";
	main_menu_frame2[8] = "             113     11311111176111112  11111176   113   1111111311111112              ";
	main_menu_frame2[9] = "             113     11311755112117556  11755112   113   1175511345555113              ";
	main_menu_frame2[10] = "             111111121131111117611111112113  113   113   113  11311111113              ";
	main_menu_frame2[11] = "             455555564564555556 45555556456  456   456   456  45645555556              ";
	main_menu_frame2[12] = "                                                                                       ";
	main_menu_frame2[13] = "                                          Start                                        ";
	main_menu_frame2[14] = "                                      8 Controls                                       ";

	main_menu_frame3[0] = "112     111112 1111112 112   1121111112 1121112   112111111112112  112 1111112 11111112";
	main_menu_frame3[1] = "113    11755112117551124112 11761175511211311112  113455117556113  11311755511211755556";
	main_menu_frame3[2] = "113    1111111311111176 4111176 11111176113117112 113   113   11111113113   11311111112";
	main_menu_frame3[3] = "113    1175511311755112  41176  117551121131134112113   113   11755113113   11345555113";
	main_menu_frame3[4] = "1111112113  11311111176   113   113  113113113 411113   113   113  11341111117611111113";
	main_menu_frame3[5] = "4555556456  4564555556    456   456  456456456  45556   456   456  456 4555556 45555556";
	main_menu_frame3[6] = "             112     1121111112 111111121111112 111111112 111112 11111112              ";
	main_menu_frame3[7] = "             113     1131175511211755556117551124551175561175511211755556              ";
	main_menu_frame3[8] = "             113     11311111176111112  11111176   113   1111111311111112              ";
	main_menu_frame3[9] = "             113     11311755112117556  11755112   113   1175511345555113              ";
	main_menu_frame3[10] = "             111111121131111117611111112113  113   113   113  11311111113              ";
	main_menu_frame3[11] = "             455555564564555556 45555556456  456   456   456  45645555556              ";
	main_menu_frame3[12] = "                                                                                       ";
	main_menu_frame3[13] = "                                          Start                                        ";
	main_menu_frame3[14] = "                                        Controls                                       ";

	difficulty_line_1 = "                                       Difficulty                                      ";
	difficulty_line_2 = "                                     8 Difficulty                                      ";

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
	if (main_menu_3 == true)
	{
		for (int i = 0; i < 15; ++i)
		{
			for (int a = 0; a < 87; ++a)
			{
				x.X = a;
				x.Y = i + 1;
				currentchar = main_menu_frame3[i][a];
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

	if (difficulty_option == true)
	{
		x.Y = 16;
		if (difficulty1 == true)
		{
			for (int i = 0; i < 87; ++i)
			{
				x.X = i;
				currentchar = difficulty_line_1[i];
				g_Console.writeToBuffer(x, currentchar, 0x1A);
			}
		}
		if (difficulty2 == true)
		{
			for (int i = 0; i < 87; ++i)
			{
				x.X = i;
				currentchar = difficulty_line_2[i];
				switch (currentchar)
				{
				case('8'):
					currentchar = 62;
					break;
				}
				g_Console.writeToBuffer(x, currentchar, 0x1A);
			}
		}
	}
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
			x.X = a + 2;
			x.Y = i + 10;
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
		if (g_abKeyPressed[K_DOWN])
		{
			if (difficulty_option == true)
			{
				main_menu_2 = false;
				main_menu_3 = true;
				difficulty1 = false;
				difficulty2 = true;
				bSomethingHappened = true;
			}

		}
	}
	else if (difficulty2 == true && difficulty_option == true)
	{
		if (g_abKeyPressed[K_UP])
		{
			main_menu_2 = true;
			main_menu_3 = false;
			difficulty1 = true;
			difficulty2 = false;
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

/*
what happens when the player runs into an entity?
the game checks which entity they ran into and render the corresponding text
eg: run into mob1
check that player run into mob1
access text relating to mob1
render text of mob1
after finish clean textbox
*/


//COMBAT RENDERING STUFF and changing of gamestate
void duration(EGAMESTATES * gameState, double dt) // timer for the combat
{
	totalTime += dt;
	if (totalTime > 10.0)
	{
		h = 0;
		moveAllow = true;
		*gameState = S_GAME;
	}
}

bool ansChecker(int passer, string str)
{
	char input = 0;
	char correct;
	correct = str[passer];
	if (g_abKeyPressed[K_1])
	{
		input = 49;
	}
	if (g_abKeyPressed[K_2])
	{
		input = 50;
	}
	if (g_abKeyPressed[K_3])
	{
		input = 51;
	}

	if (input == correct)
	{
		g_eGameState = S_GAME;
		return true;
	}
	else
	{
		g_eGameState = S_SPLASHSCREEN;
		return false;
	}
}

void COMBAT() // runs when gamestate is in combat
{

	if (h == g)
	{
		textPicker(&continueRender, &bArray[18], &ansPasser); // ansPasser is for the array for answers
		h++;
	}
	spamPrint(continueRender);
}


void spamPrint(string input)
{
	const WORD colors[] = {
		0x1F, 0x2B, 0x3C, 0x4D, 0x5E, 0x6F,
		0xA1, 0xB2, 0xC3, 0xD4, 0xE5, 0xF6
	};

	COORD textCoord;
	textCoord.X = 0;
	textCoord.Y = 18;


	g_Console.writeToBuffer(textCoord, input, colors[0]);
}

void initAns(ifstream * mobans, string * ansStr)
{
	getline(*mobans, *ansStr);
}

void textPicker(string * continueRender, bool * boolarray, int * passer) // randomly picks a mob text to print
{
	srand(time(nullptr));
	*passer = rand() % 18 + 1;
	if (!boolarray[*passer - 1])
	{
		switch (*passer)
		{
		case 1:
			*continueRender = mob1.monsterQn;
			break;
		case 2:
			*continueRender = mob2.monsterQn;
			break;
		case 3:
			*continueRender = mob3.monsterQn;
			break;
		case 4:
			*continueRender = mob4.monsterQn;
			break;
		case 5:
			*continueRender = mob5.monsterQn;
			break;
		case 6:
			*continueRender = mob6.monsterQn;
			break;
		case 7:
			*continueRender = mob7.monsterQn;
			break;
		case 8:
			*continueRender = mob8.monsterQn;
			break;
		case 9:
			*continueRender = mob9.monsterQn;
			break;
		case 10:
			*continueRender = mob10.monsterQn;
			break;
		case 11:
			*continueRender = mob11.monsterQn;
			break;
		case 12:
			*continueRender = mob12.monsterQn;
			break;
		case 13:
			*continueRender = mob13.monsterQn;
			break;
		case 14:
			*continueRender = mob14.monsterQn;
			break;
		case 15:
			*continueRender = mob15.monsterQn;
			break;
		case 16:
			*continueRender = mob16.monsterQn;
			break;
		case 17:
			*continueRender = mob17.monsterQn;
			break;
		case 18:
			*continueRender = mob18.monsterQn;
			break;
		default:
			*continueRender = "test";
			break;
		}
		boolarray[*passer - 1] = false;
	}
}

//END OF COMBAT RENDERING