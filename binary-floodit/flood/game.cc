#include "game.h"
#include "cell.h"
#include "PRNG.h"
#include "textdisplay.h"
#include <iostream>
using namespace std;

Game::Game(int size, int turns) : gridSize(size), turns(turns){
 this->display = new TextDisplay(gridSize);
 Cell::addDisplay(this->display); // attach this textdisplay to all the cell as static member
 grid = new Cell *[size]; // initialize a cell matrix
 for (int i = 0; i < size; ++i) {
  grid[i] = new Cell[size];
  for (int j = 0; j < size; ++j) {
   grid[i][j].setCoords(i, j); // tell this cell its row and column
   grid[i][j].setState(prng(4)); // give this cell a random state
  }
 } // end of initialize grid matrix for loop
 
 // add neighbors for each cell
 for (int i = 0; i < size; ++i) {
  for (int j = 0; j < size; ++j) { // add neighbours to each cell according to its position in martrix
   if (i != 0) grid[i][j].addNeighbour(&(grid[i-1][j]));
   if (i != (size - 1)) grid[i][j].addNeighbour(&(grid[i+1][j]));
   if (j != 0) grid[i][j].addNeighbour(&(grid[i][j-1])) ;
   if (j != (size - 1)) grid[i][j].addNeighbour(&(grid[i][j+1]));
  }
 }//end of adding neighbors for loop
} //constructor


Game::~Game() {
 for (int i = 0; i < gridSize; ++i) {
  delete [] grid[i]; // delete column
 }
 delete [] grid; // delete row
} //destructor

int Game::getTurns() {
 return this->turns;
} // return how many turns left


bool Game::isWon() { 
  for (int i = 0; i < gridSize; ++i)
    for (int j = 0; j < gridSize; ++j)
	if (grid[i][j].getState() != grid[0][0].getState())
		return false; // check states of each cells and compare them with (0,0) cell
	return true;
} // give a bool that determin the result of the game

void Game::change(int state) {
 if (state != grid[0][0].getState()){ 
 int cellstate = grid[0][0].getState();
 grid[0][0].notify(state, cellstate); // tell (0,0) cell to change its state
 }
 turns = turns - 1;
} 

void Game::print() {
 display->print(); // print matrix
 if (turns == 1) {
  cout << "1 move left" << endl; // different cases
 } else {
  cout << turns << " moves left" << endl;
 }
 
} 

void Game::addDisplay(TextDisplay * display){
 this->display = display;
}


