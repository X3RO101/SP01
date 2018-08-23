#ifndef _GAME_H
#define _GAME_H

#include "Framework\timer.h"
#include <stdio.h>

extern CStopWatch g_swTimer;
extern bool g_bQuitGame;

// Enumeration to store the control keys that your game will have
enum EKEYS
{
    K_UP,
    K_DOWN,
    K_LEFT,
    K_RIGHT,
    K_ESCAPE,
    K_SPACE,
    K_COUNT,
	K_1,
	K_2,
	K_3
};

// Enumeration for the different screen states
enum EGAMESTATES
{
    S_SPLASHSCREEN,
	S_CONTROLS,
    S_GAME,
    S_COUNT,
	S_DEATH,
	S_PAUSE,
	S_COMBAT,
	S_DIFFICULTY
};

// struct for the game character
struct SGameChar
{
    COORD m_cLocation;
    bool  m_bActive;
};

// struct for monsters in the game
struct monstatus
{
	COORD location;
	bool alive;
};

void init        ( void );      // initialize your variables, allocate memory, etc
void getInput    ( void );      // get input from player
void update      ( double dt ); // update the game and the state of the game
void render      ( void );      // renders the current state of the game to the console
void shutdown    ( void );      // do clean up, free memory

void splashScreenWait();    // waits for time to pass in splash screen
void gameplay();            // gameplay logic
void moveCharacter();       // moves the character, collision detection, physics, etc
void processUserInput();    // checks if you should change states or do something else with the game, e.g. pause, exit
void clearScreen();         // clears the current screen and draw from scratch 
void renderGame();          // renders the game stuff
void renderMap();           // renders the map to the buffer first
void renderCharacter();     // renders the character into the buffer
void renderFramerate();     // renders debug information, frame rate, elapsed time, etc
void renderToScreen();      // dump the contents of the buffer to the screen, one frame worth of game
// void combat();
//runs combat functions



void health();				// health lowers if player takes damage and when player dies, screen goes to game over screen
void game_over();			// shows the game over screen if the player dies
void main_menu();			// the basic main menu screen when the player starts the game
void scoresystem();			// function that increases the score when the player kills a mob
void main_menu_option();	// function that changes between the start button and controls button in the main menu
void control_screen();		// screen that shows the controls
void control_screen_back();	// function to go back to main menu
void pause_select();		// 
void pause_screen();		// 
void difficulty_screen();	//
void difficulty_choose();
void mobmovement(int i);
void movemobs();

#endif // _GAME_H