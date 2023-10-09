#include "Gameboard.h"
#include "Playerboard.h"
#include "Ship.h"

void Playerboard::createBoard(string board[ROWS][COLS])
{
	string emptyPlayerBoard[ROWS][COLS];

	string ocean = "-";

	// Initializes player board
	for (int r = 0; r < ROWS; r++)
	{
		for (int c = 0; c < COLS; c++)
		{
			emptyPlayerBoard[r][c] = ocean;
		}
	}

}

bool Playerboard::getUserInput(int* userR, int* userC, int* userDir)
{
	int minValidRowOrCol = -1;
	int maxValidRowOrCol = 9;
	
	// User ship placement phase ONLY
	// This checks for valid user input, making sure the values chosen are within -1 and 9
	// Reprompt user if they aren't; if the value entered is -1 (sentinel), returns true and exits game
	// Else, returns false after user picks row, col, and direction
	cout << "\nEnter row [0-9] you want to place ship (Exit: -1): ";
InvalidRow:
	cin >> *userR;
	if (*userR > maxValidRowOrCol || *userR < minValidRowOrCol)
	{
		cout << "\nInvalid row! Please enter valid row [0-9] (Exit: -1): ";
		goto InvalidRow;
	}
	if (*userR == -1)
	{
		return true;
	}

	cout << "\nEnter column [0-9] you want to place ship (Exit: -1): ";
InvalidCol:
	cin >> *userC;
	if (*userC > maxValidRowOrCol || *userC < minValidRowOrCol)
	{
		cout << "\nInvalid col! Please enter valid col [0-9]: ";
		goto InvalidCol;
	}
	if (*userC == -1)
	{
		return true;
	}

	cout << "\nWhich direction? [1: North 2: East 3: South 4: West] (Exit: -1): ";

	cin >> *userDir;
	if (*userDir == -1)
	{
		return true;
	}
	
	return false;
}

bool Playerboard::attackInput(int* userR, int* userC)
{
	int minValidRowOrCol = -1;
	int maxValidRowOrCol = 9;

	// User attack phase ONLY
	// This checks for valid user input, making sure the values chosen are within -1 and 9
	// Reprompt user if they aren't; if the value entered is -1 (sentinel), returns true and exits game
	// Else, returns false and saves value of row and col chosen
	cout << "\n\nEnter row [0-9] you want to attack! (Exit: -1): ";
InvalidRow2:
	cin >> *userR;
	if (*userR > maxValidRowOrCol || *userR < minValidRowOrCol)
	{
		cout << "\nInvalid row! Please enter valid row [0-9] (Exit: -1): ";
		goto InvalidRow2;
	}
	if (*userR == -1)
	{
		return true;
	}

	cout << "\nEnter column [0-9] you want to attack! (Exit: -1): ";
InvalidCol2:
	cin >> *userC;
	if (*userC > maxValidRowOrCol || *userC < minValidRowOrCol)
	{
		cout << "\nInvalid col! Please enter valid col [0-9]: ";
		goto InvalidCol2;
	}
	if (*userC == -1)
	{
		return true;
	}
	return false;
}

string Playerboard::placeShips(string playerBoard[ROWS][COLS], int numShip, int* r, int* c, int* d)
{
	// Creates instance of userboard
	
	int directions = *d;
	string spaceForShip;

	// Creates five ship instances
	Ship frigate, sub, destroyer, battleship, aircraftCarrier;

	// Sets ship sizes
	frigate.setShipSize(2);
	sub.setShipSize(3);
	destroyer.setShipSize(3);
	battleship.setShipSize(4);
	aircraftCarrier.setShipSize(5);

	// Sets ship initial
	frigate.setShipLetter("F");
	sub.setShipLetter("S");
	destroyer.setShipLetter("D");
	battleship.setShipLetter("B");
	aircraftCarrier.setShipLetter("A");

	// Sets ship name
	frigate.setShipName("Frigate");
	sub.setShipName("Submarine");
	destroyer.setShipName("Destroyer");
	battleship.setShipName("Battleship");
	aircraftCarrier.setShipName("Aircraft Carrier");

	int shipSize[5] = { frigate.getShipSize(), sub.getShipSize(), destroyer.getShipSize(), battleship.getShipSize(), aircraftCarrier.getShipSize() };
	string shipLetter[5] = { frigate.getShipLetter(), sub.getShipLetter(), destroyer.getShipLetter(), battleship.getShipLetter(), aircraftCarrier.getShipLetter() };
	string shipName[5] = { frigate.getShipName(), sub.getShipName(), destroyer.getShipName(), battleship.getShipName(), aircraftCarrier.getShipName() };

	// If ship is North or South, calls northOrSouth and tries to place a ship vertically
	// Else, it tries to place ship horizontally eastOrWest
	if (*d % 2 == 0)
	{
		spaceForShip = Playerboard::northOrSouth(playerBoard, shipLetter, shipSize, numShip, r, c, d);
	}
	else
	{
		spaceForShip = Playerboard::eastOrWest(playerBoard, shipLetter, shipSize, numShip, r, c, d);
	}	
	return spaceForShip;
}

string Playerboard::northOrSouth(string playerBoard[ROWS][COLS], string letter[], int size[], int numShip, int* userR, int* userC, int* userDir)
{
	Gameboard checkSpaces;
	bool emptyspace;
	string collision = "col";
	string endOfWorld = "end";
	string placeShip = "place";
	int minRowOrCol = 0;
	int y = 0;

	// This loop executes until all spots have been filled based on ship size
	// First, it checks if user direction is North or South
	// Then, it checks if the ship will fit in the spot
	// Lastly, it will check if the spot it wants to place the ship at is empty
	// If everything is good, the ship is placed and y incremented
	// Else, depending on the condition not met, returns a message on whether a ship encountered or is out of range
	while (y < size[numShip])
	{
		if (*userDir == North)
		{
			if (*userR - (size[numShip] - 1) >= minRowOrCol)
			{
				emptyspace = checkSpaces.isEmpty(playerBoard, letter, size, numShip, *userR, *userC, *userDir);

				if (emptyspace == true)
				{
					for (int x = 0; x < size[numShip]; x++)
					{
						playerBoard[*userR - y][*userC] = letter[numShip];
						y++;
					}
				}
				else
				{
					return collision;
				}
			}
			else
			{
				return endOfWorld;
			}
		}
		else
		{
			if (*userR + (size[numShip] - 1) < ROWS)
			{	
				emptyspace = checkSpaces.isEmpty(playerBoard, letter, size, numShip, *userR, *userC, *userDir);

				if (emptyspace == true)
				{
					for (int x = 0; x < size[numShip]; x++)
					{
						playerBoard[*userR + y][*userC] = letter[numShip]; // increment row
						y++;
					}	
				}
				else
				{
					return collision;
				}
			}
			else
			{
				return endOfWorld;
			}
		}
	}
	return placeShip;
}

string Playerboard::eastOrWest(string playerBoard[ROWS][COLS], string letter[], int size[], int numShip, int* userR, int* userC, int* userDir)
{
	Gameboard checkSpaces;
	bool emptyspace;
	string collision = "col";
	string endOfWorld = "end";
	string placeShip = "place";
	int minRowOrCol = 0;
	int y = 0;
	
	// This loop executes until all spots have been filled based on ship size
	// First, it checks if user direction is East or West
	// Then, it checks if the ship will fit in the spot
	// Lastly, it will check if the spot it wants to place the ship at is empty
	// If everything is good, the ship is placed and y incremented
	// Else, depending on the condition not met, returns a message on whether a ship encountered or is out of range

	while (y < size[numShip])
	{
		if (*userDir == East)
		{
			if (*userC + (size[numShip] - 1) < COLS)
			{
				emptyspace = checkSpaces.isEmpty(playerBoard, letter, size, numShip, *userR, *userC, *userDir);

				if (emptyspace == true)
				{
					for (int x = 0; x < size[numShip]; x++)
					{
						playerBoard[*userR][*userC + y] = letter[numShip];
						y++;
					}
				}
				else
				{
					return collision;
				}
			}
			else
			{
				return endOfWorld;
			}
		}
		else
		{
			if (*userC - (size[numShip] - 1) >= minRowOrCol)
			{
				emptyspace = checkSpaces.isEmpty(playerBoard, letter, size, numShip, *userR, *userC, *userDir);

				if (emptyspace == true)
				{
					for (int x = 0; x < size[numShip]; x++)
					{
						playerBoard[*userR][*userC - y] = letter[numShip];
						y++;
					}
				}
				else
				{
					return collision;
				}
			}
			else
			{
				return endOfWorld;
			}
		}
	}
	return placeShip;
}

// Function chooses direction during ship placement phase, saves in list to pass into gameboard
int Playerboard::chooseDirection(int *userD, int &funcCount)
{
	// Checks to see if input direction is one of enums (input direction decremented by one to match enum actual value)
StartOver:
	switch (*userD)
	{
	case 1:
		funcCount++;
		return North;
		break;
	case 2:
		funcCount++;
		return East;
		break;
	case 3:
		funcCount++;
		return South;
		break;
	case 4:
		funcCount++;
		return West;
		break;
	default:
		cout << "Invalid input! Re-enter direction [1: North 2: East 3: South 4: West]: ";
		cin >> *userD;
		goto StartOver;
	}
}

