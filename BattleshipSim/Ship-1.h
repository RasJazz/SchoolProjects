#ifndef SHIP_H
#define SHIP_H

#include "Gameboard.h"

class Ship : protected Gameboard
{
private:
	string shipName;
	string shipLetter;
	int shipSize;
	int shipDirection;

public:
	
	//Constructors
	Ship()
	{
		shipName = " ";
		string shipLetter = " ";
		int shipSize = 0;
		int shipDirection = 0;
	}

	Ship(string name, string letter, int size) : Gameboard()
	{
		shipName = name;
		shipLetter = letter;
		shipSize = size;
	}

	Ship(string name, string letter, int size, int x, int y, int direction) : Gameboard()
	{
		shipName = name;
		shipLetter = letter;
		shipSize = size;
		xCoord = x;
		yCoord = y;
		shipDirection = direction;
	}

	void createUserShips(string*, int*, string*, int);

	void setShipName(string);
	string getShipName();

	void setShipLetter(string);
	string getShipLetter();

	void setShipSize(int);
	int getShipSize();

};
#endif