#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <list>

using namespace std;

// Global variables

const int ROWS = 10;
const int COLS = 10;
const int numberOfShips = 5;

class Gameboard
{
protected:
	enum Directions { North, East, South, West };

public:
	int xCoord;
	int yCoord;
	int direction;
	// Default Constructor
	Gameboard()
	{
		xCoord = 0;
		yCoord = 0;
		direction = 0;
	}
	Gameboard(int x, int y, int dir)
	{
		xCoord = x;
		yCoord = y;
		direction = dir;
	}

	const int getXCoord() const
		{ return xCoord; }

	const int getYCoord() const
		{ return yCoord; }

	const int getDirection() const
		{ return direction; }
	
	void introMessage(int);
	void createBoard(string[ROWS][COLS], string [ROWS][COLS], string[ROWS][COLS]);
	bool isEmpty(string[ROWS][COLS], string[], int[], int, int, int, int);
	bool playerAttack(string[ROWS][COLS], string[ROWS][COLS], int, int, int);
	void enemyAttack(string[ROWS][COLS]);
	bool checkBattlefield(string[ROWS][COLS], string[ROWS][COLS]);
	void printPlayerBoard(string[ROWS][COLS], string);
	void printAttackBoard(string[ROWS][COLS]);
	void printBattlefield(string[ROWS][COLS], string[ROWS][COLS], string);
	
};
#endif
