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
#include "levelgen.h"
#include "tilemanager.h"

char map[15][87];
int lvlcleared = 0;
string mapstring = levelgen(lvlcleared);
int changeinlvl = 0;

double  g_dElapsedTime;
double  g_dDeltaTime;
bool    g_abKeyPressed[K_COUNT];

// Game specific variables here
SGameChar   g_sChar;
EGAMESTATES g_eGameState = S_SPLASHSCREEN;
double  g_dBounceTime; // this is to prevent key bouncing, so we won't trigger keypresses more than once

// Console object
Console g_Console(87, 30, "SP1 Framework");

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
		//case S_COMBAT :
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
		}
		else if (touchend(map, g_sChar.m_cLocation.Y, g_sChar.m_cLocation.X) == true)
		{
			//run text for end door password, if correct, do lvlcleared++ to change lvl on next render, reset pos of player
			lvlcleared++;
			g_sChar.m_cLocation.X = g_Console.getConsoleSize().X / 2;
			g_sChar.m_cLocation.Y = 5;
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

			
		}
		else if (touchend(map, g_sChar.m_cLocation.Y, g_sChar.m_cLocation.X) == true)
		{
			//run text for end door password, if correct, do lvlcleared++ to change lvl on next render, reset pos of player
			lvlcleared++;
			g_sChar.m_cLocation.X = g_Console.getConsoleSize().X / 2;
			g_sChar.m_cLocation.Y = 5;
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

		
		}
		else if (touchend(map, g_sChar.m_cLocation.Y, g_sChar.m_cLocation.X) == true)
		{
			//run text for end door password, if correct, do lvlcleared++ to change lvl on next render, reset pos of player
			lvlcleared++;
			g_sChar.m_cLocation.X = g_Console.getConsoleSize().X / 2;
			g_sChar.m_cLocation.Y = 5;
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
		}
		else if (touchend(map, g_sChar.m_cLocation.Y, g_sChar.m_cLocation.X) == true)
		{
			//run text for end door password, if correct, do lvlcleared++ to change lvl on next render, reset pos of player
			lvlcleared++;
			g_sChar.m_cLocation.X = g_Console.getConsoleSize().X / 2;
			g_sChar.m_cLocation.Y = 5;
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
        g_bQuitGame = true;    
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
    g_Console.writeToBuffer(c, "Labyrinthos Libertas", 0x03); //Title of the game here
    c.Y += 1;
    c.X = g_Console.getConsoleSize().X / 2 - 20;
    g_Console.writeToBuffer(c, "Press <Space> to change character colour", 0x09);//color to change to if space bar is pressed
    c.Y += 1;
    c.X = g_Console.getConsoleSize().X / 2 - 9;
    g_Console.writeToBuffer(c, "Press 'Esc' to quit", 0x09);//quit
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
    
	string rows;
	string cols;
	string filename;
	int y;
	int x;
	

	if (lvlcleared == 0)
	{
		filename += "lvl1.txt";
	}
	else if (lvlcleared == 1)
	{
		filename += "lvl2.txt";
	}
	else if (lvlcleared == 2)
	{
		filename += "lvl3.txt";
	}
	else if (lvlcleared == 3)
	{
		filename += "lvl4.txt";
	}
	else if (lvlcleared == 4)
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

	/*start here
	string filename;

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

void combat()
{

}