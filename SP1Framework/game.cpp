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

using namespace std;

double  g_dElapsedTime;
double  g_dDeltaTime;
bool    g_abKeyPressed[K_COUNT];

bool isdead = false;				// bool when player loses to the mob once
bool killmob = false;				// bool for when player kills the mob
int healthpoints = 3;				// number of lives player has
int score = 0;						// player score
bool dies = false;					// when the player loses all healthpoints
bool main_menu_screen = true;		// to check if player is in the main menu
bool main_menu_screen_1 = true;		// frame 1 of main menu, to ensure which page of the main menu player is at
bool main_menu_screen_2 = false;	//frame 2 of main menu

// Game specific variables here
SGameChar   g_sChar;
EGAMESTATES g_eGameState = S_SPLASHSCREEN;
double  g_dBounceTime; // this is to prevent key bouncing, so we won't trigger keypresses more than once

// Console object
Console g_Console(80, 25, "Labyrinthos Libertas");

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
        case S_SPLASHSCREEN : splashScreenWait(); // game logic for the splash screen
            break;
        case S_GAME: gameplay(); // gameplay logic when we are in the game
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
        g_bQuitGame = true;

	dies = true;
	game_over();
}

void clearScreen()
{
    // Clears the buffer with this colour attribute
    g_Console.clearBuffer(0x1F);
}

void renderSplashScreen()  // renders the splash screen
{
	COORD c = g_Console.getConsoleSize();
	c.Y /= 3;
	c.X = c.X / 2 - 9;
	g_Console.writeToBuffer(c, "A game in 3 seconds", 0x03);
	c.Y += 1;
	c.X = g_Console.getConsoleSize().X / 2 - 20;
	g_Console.writeToBuffer(c, "Press <Space> to change character colour", 0x09);
	c.Y += 1;
	c.X = g_Console.getConsoleSize().X / 2 - 9;
	g_Console.writeToBuffer(c, "Press 'Esc' to quit", 0x09);
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

char health()
{
	//Should the player's health turn to 0, the game will end, leading to the end screen
	if (healthpoints = 0)
	{
		dies = true;
		game_over();
	}

	//If the player loses, then bool(isdead) will be true
	//The player will then lose 1 healthpoint, and then the bool will then return to being false
	if (isdead = true)
	{
		healthpoints--;
		isdead = false;
	}

	return healthpoints;
}

void game_over()
{
	//set a name to a string variable
	//ifstream file(note: file should be in the same folder as the err solution)
	//file.open(filename)
	//use the writeToBuffer (check the framework)

	if (dies == true)
	{
		string deathscreen;
		ifstream deathscreenfile("game_over_screen.txt");
		if (deathscreenfile.is_open())
		{
			struct _COORD x;
			x.X = 0;
			x.Y = 0;
			while (getline(deathscreenfile, deathscreen))
			{
				g_Console.writeToBuffer(x, deathscreen, 0x09);
				x.Y += 1;
			}
			deathscreenfile.close();
		}
	}
}

void scoresystem()
{
	if (killmob) //When a mob is killed, the bool killmob becomes true, then the score increasese by the health the player has left
	{
		score++;
		score += healthpoints;
		killmob = false;
	}

}

void main_menu()
{
	while (main_menu_screen == true)
	{
		if (g_abKeyPressed[K_UP])
		{
			main_menu_screen_1 = true;
			main_menu_screen_2 = false;
			string mainmenu1;
			ifstream mainmenufile1("main_menu_frame_1.txt");
			if (mainmenufile1.is_open())
			{
				struct _COORD x;
				x.X = 0;
				x.Y = 0;
				while (getline(mainmenufile1, mainmenu1))
				{
					g_Console.writeToBuffer(x, mainmenu1, 0x09);
					x.Y += 1;
				}
				mainmenufile1.close();
			}
		}
		if (g_abKeyPressed[K_DOWN])
		{
			main_menu_screen_1 = false;
			main_menu_screen_2 = true;
			string mainmenu2;
			ifstream mainmenufile2("main_menu_frame_1.txt");
			if (mainmenufile2.is_open())
			{
				struct _COORD x;
				x.X = 0;
				x.Y = 0;
				while (getline(mainmenufile2, mainmenu2))
				{
					g_Console.writeToBuffer(x, mainmenu2, 0x09);
					x.Y += 1;
				}
				mainmenufile2.close();
			}
		}
	}
}