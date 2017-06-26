#include "PRNG.h"
#include "cell.h"
#include "game.h"
#include "textdisplay.h"
#include <iostream>
#include <string>
#include <sstream>
#include <limits>
#include <unistd.h>
using namespace std;

PRNG prng; // declare global value prng

int main(int argc, char *argv[]) {
 try {
  int size = 10, seed = getpid(), moves = 20; // set default value for size, seed and turns
  for (int i = 1; i < argc; i += 2){ // read in each options and numbers
    if (string(argv[i]) == "-size") {
	size = stoi(string(argv[i+1])); // translate char* to string, then to integer
        if (size < 2) throw 1; // throw exception and print error message
      }
    else if (string(argv[i]) == "-seed")
	seed = stoi(string(argv[i+1]));
    else if (string(argv[i]) == "-moves") {
	moves = stoi(string(argv[i+1]));
        if (moves < 1) throw 1;
     } else {
      throw 1; // throw incorrect option
     }
    }
  // -----------------------------------------------
  // set the global value PRNG-----
    prng.seed(seed); // seed is got from read input
  // -----------------------------------------------
  Game mygame(size, moves); // new matrix of cells
  mygame.print(); // print out our matrix first
  string state; // prepare for reading in string input

  while(cin >> state) { // read in a string
   stringstream ss(state); 
   int newstate = -1;
   if (ss >> newstate){
   if ((newstate < 0) || (newstate > 4)) { // determin if this number is not a correct state
    cerr << "Invalid move" << endl;
    continue; // skip remaining loop and start a new loop
   }
   mygame.change(newstate); // change cell state in matrix
   mygame.print(); // print out corrent matrix
   int remain = mygame.getTurns(); // determine if run out of moves
   if (mygame.isWon()) { // determine if we win
    cout << "Won" << endl;
    break; // exit the loop
   }
   if (remain == 0) { // determin if there is still some moves
    cout << "Lost" << endl;
    break; // exit the loop
   }
  }
  else { // this is when we do not get a number input, but other things
    cerr << "Invalid move" << endl; // produce error message
  }
} // end of while loop
  
 } catch (int i) { // error message
  cerr <<  "Usage: ./floodit-sample [ -size N (width and height of game ) >= 2) ] | [ -moves M (number of moves until game is over) >= 1) ] | [ -seed S (seed for random-number generator (1..INT_MAX)) ]" << endl;
 }
}




