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

// Game specific variables here
SGameChar   g_sChar;
EGAMESTATES g_eGameState = S_SPLASHSCREEN;
double  g_dBounceTime; // this is to prevent key bouncing, so we won't trigger keypresses more than once

// Console object
Console g_Console(87, 30, "                                                             Labyrinthos Libertas");

//--------------------------------------------------------------
// Purpose  : Initialisation function
//            Initialize variables, allocate memory, load data from file, etc. 
//            This is called once before entering into your main loop
// Input    : void
// Output   : void
//--------------------------------------------------------------
void init( void )
{
    // Set precision for floating point output
    g_dElapsedTime = 0.0;
    g_dBounceTime = 0.0;

    // sets the initial state for the game
    g_eGameState = S_SPLASHSCREEN;

    g_sChar.m_cLocation.X = g_Console.getConsoleSize().X / 2;
    g_sChar.m_cLocation.Y = g_Console.getConsoleSize().Y / 2;
    g_sChar.m_bActive = true;
    // sets the width, height and the font name to use in the console
    g_Console.setConsoleFont(0, 16, L"Consolas");
}

//--------------------------------------------------------------
// Purpose  : Reset before exiting the program
//            Do your clean up of memory here
//            This is called once just before the game exits
// Input    : Void
// Output   : void
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
// Output   : void
//--------------------------------------------------------------
void getInput( void )
{    
    g_abKeyPressed[K_UP]     = isKeyPressed(VK_UP);
    g_abKeyPressed[K_DOWN]   = isKeyPressed(VK_DOWN);
    g_abKeyPressed[K_LEFT]   = isKeyPressed(VK_LEFT);
    g_abKeyPressed[K_RIGHT]  = isKeyPressed(VK_RIGHT);
    g_abKeyPressed[K_SPACE]  = isKeyPressed(VK_SPACE);
    g_abKeyPressed[K_ESCAPE] = isKeyPressed(VK_ESCAPE);
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
// Output   : void
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
    }
}
//--------------------------------------------------------------
// Purpose  : Render function is to update the console screen
//            At this point, you should know exactly what to draw onto the screen.
//            Just draw it!
//            To get an idea of the values for colours, look at console.h and the URL listed there
// Input    : void
// Output   : void
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
    bool bSomethingHappened = false;
    if (g_dBounceTime > g_dElapsedTime)
        return;

    // Updating the location of the character based on the key press
    // providing a beep sound whenver we shift the character
    if (g_abKeyPressed[K_UP] && g_sChar.m_cLocation.Y > 0)
    {
        //Beep(1440, 30);
        g_sChar.m_cLocation.Y--;
        bSomethingHappened = true;
    }
    if (g_abKeyPressed[K_LEFT] && g_sChar.m_cLocation.X > 0)
    {
        //Beep(1440, 30);
        g_sChar.m_cLocation.X--;
        bSomethingHappened = true;
    }
    if (g_abKeyPressed[K_DOWN] && g_sChar.m_cLocation.Y < g_Console.getConsoleSize().Y - 1)
    {
        //Beep(1440, 30);
        g_sChar.m_cLocation.Y++;
        bSomethingHappened = true;
    }
    if (g_abKeyPressed[K_RIGHT] && g_sChar.m_cLocation.X < g_Console.getConsoleSize().X - 1)
    {
        //Beep(1440, 30);
        g_sChar.m_cLocation.X++;
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
        g_dBounceTime = g_dElapsedTime + 0.125; // 125ms should be enough
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
}

void renderGame()
{
    renderMap();        // renders the map to the buffer first
    renderCharacter();  // renders the character into the buffer
}

void renderMap()
{
    // Set up sample colours, and output shadings
    const WORD colors[] = {
        0x1A, 0x2B, 0x3C, 0x4D, 0x5E, 0x6F,
        0xA1, 0xB2, 0xC3, 0xD4, 0xE5, 0xF6
    };

    COORD c;
    for (int i = 0; i < 12; ++i)
    {
        c.X = 5 * i;
        c.Y = i + 1;
        colour(colors[i]);
        g_Console.writeToBuffer(c, " °±²Û", colors[i]);
    }

	string healthtext = "Health : ";
	COORD x;
	char currentchar;
	currentchar = 3;
	x.X = 1;
	x.Y = 13;
	for (int i = 0; i < 9; ++i)
	{
		g_Console.writeToBuffer(x, healthtext[i], 0x09);
		x.X++;
	}
	for (int i = 0; i < healthpoints; ++i)
	{
		g_Console.writeToBuffer(x, currentchar, 0x09);
		x.X++;
	}

	x.X = 1;
	x.Y = 14;
	string pointstext = "Score : ";
	ostringstream str1;
	str1 << score;
	string scorestr = str1.str();
	for (int i = 0; i < 8; ++i)
	{
		g_Console.writeToBuffer(x, pointstext[i], 0x09);
		x.X++;
	}
	for (int i = 0; i < scorestr.length(); ++i)
	{
		g_Console.writeToBuffer(x, scorestr[i], 0x09);
		x.X++;
	}
}

void renderCharacter()
{
    // Draw the location of the character
    WORD charColor = 0x0C;
    if (g_sChar.m_bActive)
    {
        charColor = 0x0A;
    }
    g_Console.writeToBuffer(g_sChar.m_cLocation, (char)1, charColor);
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
			g_Console.writeToBuffer(x, currentchar, 0x09);
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
				g_Console.writeToBuffer(x, currentchar, 0x09);
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
				g_Console.writeToBuffer(x, currentchar, 0x09);
			}

		}
	}
}

void control_screen()
{
	COORD x;
	char currentchar;
	string controlscreen[10];

	controlscreen[0] = "                                                                                         ";
	controlscreen[1] = "                                                                                         ";
	controlscreen[2] = "                                                                                         ";
	controlscreen[3] = "                                   MOVING UP = UP ARROW KEY                              ";
	controlscreen[4] = "                                 MOVING DOWN = DOWN ARROW KEY                            ";
	controlscreen[5] = "                                 MOVING LEFT = LEFT ARROW KEY                            ";
	controlscreen[6] = "                                MOVING RIGHT = RIGHT ARROW KEY                           ";
	controlscreen[7] = "                                                                                         ";
	controlscreen[8] = "                                                                                         ";
	controlscreen[9] = "  MAIN MENU - SPACE KEY                                                                  ";

	for (int i = 0; i < 10; ++i)
	{
		for (int a = 0; a < 87; ++a)
		{
			x.X = a;
			x.Y = i + 1;
			currentchar = controlscreen[i][a];
			g_Console.writeToBuffer(x, currentchar, 0x09);
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
	if (pause_1 == true)
	{
		if (g_abKeyPressed[K_DOWN])
		{
			pause_1 = false;
			pause_2 = true;
			pause_3 = false;
		}
		if (g_abKeyPressed[K_SPACE])
		{
			g_eGameState = S_GAME;
		}
	}
	if (pause_2 == true)
	{
		if (g_abKeyPressed[K_UP])
		{
			pause_1 = true;
			pause_2 = false;
			pause_3 = false;
		}
		if (g_abKeyPressed[K_DOWN])
		{
			pause_1 = false;
			pause_2 = false;
			pause_3 = true;
		}
		if (g_abKeyPressed[K_SPACE])
		{
			g_eGameState = S_SPLASHSCREEN;
		}
	}
	if (pause_3 == true)
	{
		if (g_abKeyPressed[K_UP])
		{
			pause_1 = false;
			pause_2 = true;
			pause_3 = false;
		}
		if (g_abKeyPressed[K_SPACE])
		{
			g_bQuitGame = true;
		}
	}
}

void pause_screen()
{

}