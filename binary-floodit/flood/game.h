#ifndef __GAME_H__
#define __GAME_H__
#include <iostream>
#include "cell.h"
#include "textdisplay.h"

class Game {
	Cell** grid;  	       // The actual grid.
	const int gridSize;    // Size of the grid.
	int turns;             // Number of turns remaining
	TextDisplay* display;  // The text display.
public:
	Game(int size, int turns); // explicit constructor
	~Game(); // destructor

	int getTurns(); // record the move remain
	bool isWon(); // determin when to terminate the file
	void change(int state);  // Changes (0,0) and all appropriate neighbours to state    // call cell?
	void print(); // print textdisplay
	void addDisplay(TextDisplay *);
};

extern PRNG prng; // set the prng as gobal value so that it is able to be attached in game.cc

#endif

