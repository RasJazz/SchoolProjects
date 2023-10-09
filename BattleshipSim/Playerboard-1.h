#ifndef PLAYERBOARD_H
#define PLAYERBOARD_H

#include "Gameboard.h"

class Playerboard : protected Gameboard
{
public:
	// Default constructor
	Playerboard()
	{ }

	// Constructor
	Playerboard(int x, int y, int userDir) : Gameboard()
	{
		xCoord = x;
		yCoord = y;
		direction = userDir;
	}

	void createBoard(string[ROWS][COLS]);
	int chooseDirection(int*, int&);
	bool getUserInput(int*, int*, int*);
	bool attackInput(int*, int*);
	string placeShips(string[ROWS][COLS], int, int*, int*, int*);
	string northOrSouth(string board[ROWS][COLS], string[], int[], int, int*, int*, int*);
	string eastOrWest(string board[ROWS][COLS], string[], int[], int, int*, int*, int*);
};

#endif
