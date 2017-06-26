#include "textdisplay.h"
#include <iostream>
using namespace std;

TextDisplay::TextDisplay(int n) : gridSize(n) {
 theDisplay = new char *[n]; // build a new matrix
 for (int i = 0; i < n; ++i) {
  theDisplay[i] = new char[n];
  for (int j = 0; j < n; ++j) {
   theDisplay[i][j] = '0';
  }
 }
} // explicit constructor

TextDisplay::~TextDisplay() {
 for (unsigned int i = 0; i < gridSize; ++i) {
  delete [] theDisplay[i];
 } 
 delete [] theDisplay;
} // destructor

void TextDisplay::notify( int r, int c, char ch) {
 theDisplay[r][c] = ch; // change the state in specific position
}

bool TextDisplay::filled() {
	return true; // I will not use this function to check, but check result in game.h
} 

void TextDisplay::print() { // print matrix
 for (unsigned int i = 0; i < gridSize; ++i) {
  for (unsigned int j = 0; j < gridSize; ++j) {
   cout << theDisplay[i][j];
  }
  cout << endl; // start a new line
 }
} // print out the matrix




