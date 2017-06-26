#ifndef __TEXTDISPLAY_H__
#define __TEXTDISPLAY_H__
#include <iostream>
#include <sstream>

class TextDisplay {
	char **theDisplay;
	unsigned const int gridSize; // gridSize not < 0
	unsigned int colours[5];
public:
	TextDisplay(int n);
	~TextDisplay();

	void notify(int r, int c, char ch);
	bool filled();
	void print();
};

#endif

