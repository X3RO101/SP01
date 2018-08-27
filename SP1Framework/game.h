#ifndef _GAME_H
#define _GAME_H


#include "tilemanager.h"
#include "Framework/console.h"
#include "Framework/timer.h"
#include "combatRender.h"
#include <stdio.h>
#include "Container.h"
//combat stuff
extern string continueRender; // for the spam printing of the question picked
extern int ansPasser; // used to get the correct answer for the question picked
extern bool bArray[18]; // so that the same question isn't picked
extern int mobAnsvvers[18]; // the array containing all the answers
extern int cAns; // the correct ans is copied into here from the array
extern int playerinput; // the input for the ans from the player
extern int g;
extern int h; // h and g used for the conditions to use the text picker
extern double totalTime; // used the the timer of the combat state
extern double timeForCOrW; // used to print correct/wrong for 1 second
extern int CORW; // used as a checker for the conditions to print correct/wrong


extern Text mob1;
extern Text mob2;
extern Text mob3;
extern Text mob4;
extern Text mob5;
extern Text mob6;
extern Text mob7;
extern Text mob8;
extern Text mob9;
extern Text mob10;
extern Text mob11;
extern Text mob12;
extern Text mob13;
extern Text mob14;
extern Text mob15;
extern Text mob16;
extern Text mob17;
extern Text mob18;


// end of combat stuff
extern CStopWatch g_swTimer;
extern bool g_bQuitGame;


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