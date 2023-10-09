#ifndef BOARD_H
#define BOARD_H

#include "Gameboard.h"

class Board : protected Gameboard
{
private:
	int xCoord;
	int yCoord;

public:
	// Default constructor
	Board()
	{ 
		xCoord = 0;
		yCoord = 0;
	}

	// Constructor
	Board(int x, int y)
	{
		xCoord = x;
		yCoord = y;
	}
	
	void createBoard(string[ROWS][COLS]);
	void populateCompBoard(string[ROWS][COLS], string[], int[], int);
	void northOrSouth(string board[ROWS][COLS], string [], int[], int, int);
	void eastOrWest(string board[ROWS][COLS], string[], int[], int, int);
	void printBoard(string[ROWS][COLS]);
};

#endif