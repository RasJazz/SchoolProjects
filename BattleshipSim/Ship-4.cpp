#include "Gameboard.h"
#include "Ship.h"

void Ship::createUserShips(string* name, int* size, string* letter, int counter)
{
	// Creates five ship instances
	// This is really only for ship info printing
	Ship info;

	cout << "\nShip: " << name[counter] << "\n";
	cout << "Size: " << size[counter] << "\n";
	cout << "Symbol: " << letter[counter];
}

void Ship::setShipName(string name)
{
	shipName = name;
}
string Ship::getShipName()
{
	return shipName;
}

void Ship::setShipLetter(string letter)
{
	shipLetter = letter;
}
string Ship::getShipLetter()
{
	return shipLetter;
}

void Ship::setShipSize(int size)
{
	shipSize = size;
}
int Ship::getShipSize()
{
	return shipSize;
}

