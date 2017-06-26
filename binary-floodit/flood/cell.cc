#include "cell.h"

using namespace std;

TextDisplay *Cell::display = NULL; // declearation of static member

void Cell::notifyNeighbours() {
 for (int i = 0; i < numNeighbours; ++i) {
  neighbours[i]->notify(state, prevState);
 }
} // tell every neighbour this cell changed
  // if they have same state, they have to change

void Cell::notifyDisplay() {
 if (state == 0) {
  display->notify(row, col, '0'); 
 } else if (state == 1) {
  display->notify(row, col, '1');
 } else if (state == 2) {
  display->notify(row, col, '2');
 } else if (state == 3) {
  display->notify(row, col, '3');
 } else {
  display->notify(row, col, '4');
 }
} // use the notify function in textdisplay to change the single state in display with given row and column


Cell::Cell() : state(0), prevState(NO_PREVIOUS), numNeighbours(0) {} // default constructor

int Cell::getState() { 
 return this->state;
} // return the state of current cell

void Cell::setState(int change) {
 prevState = state; // store the previous state
 state = change;
 notifyDisplay(); // tell display to change
} // set state, and notify it to textdisplay each time

void Cell::setCoords(int row, int col) {
 this->row = row;
 this->col = col;
} // get the row and column of current cell from game

void Cell::addNeighbour(Cell* neighbour) {
 neighbours[numNeighbours] = neighbour;
 ++numNeighbours;
} // add neighbour to the array

void Cell::addDisplay(TextDisplay* display) {
  Cell::display = display;
} // attach the given textdisplay to all the cell


void Cell::notify(int current, int previous) {
 if (previous == state) { // determin whether this cell should change state
  setState(current);
  notifyNeighbours(); // notify other neighbour that current cell has been changed
 } 
}



