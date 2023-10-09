#include "Gameboard.h"
#include "Board.h"
#include "Ship.h"

void Board::createBoard(string compBoard[ROWS][COLS])
{
	string ocean = "-";
	// Initializes the empty array
	for (int r = 0; r < ROWS; r++)
	{
		for (int c = 0; c < COLS; c++)
		{
			compBoard[r][c] = ocean;
		}
	}
}

void Board::populateCompBoard(string compBoard[ROWS][COLS], string letter[], int size[],  int numShip)
{
	// First, we get a random direction to figure out which direction the ship will be facing
	// Then, we choose a function based on whether North, South, East, West 
	int ranDirection = (rand() % (4 - 0) + 1) - 1;

	for (int x = 0; x < numShip; x++)
	{
		// If ship is North or South, calls northOrSouth and tries to place a ship vertically
		// Else, it tries to place ship horizontally East or West
		if (ranDirection % 2 == 0)
		{
			Board::northOrSouth(compBoard, letter, size, x, ranDirection);
			ranDirection = (rand() % (4 - 0) + 1) - 1;

		}
		else
		{
			Board::eastOrWest(compBoard, letter, size, x, ranDirection);
			ranDirection = (rand() % (4 - 0) + 1) - 1;

		}
	}
}

void Board::northOrSouth(string compBoard[ROWS][COLS], string letter[], int size[], int numShip, int compD)
{
	Gameboard checkSpaces;

	// Random number generators for the randomRow and randomCol placement
	bool emptyspace = false;
	int randomRow = (rand() % ROWS);
	int randomCol = (rand() % COLS);
	int minRowOrCol = 0;
	int y = 0;

	// This loop executes until all spots have been filled based on ship size
	// First, it checks if random direction is North or South
	// Then, it checks if the ship will fit in the spot
	// Lastly, it will check if the spot it wants to place the ship is empty
	// If everything is good, the ship is placed and y incremented
	// Else, regenerates random nums and starts again
	while (y < size[numShip])
	{
		if (compD == North)
		{
			if (randomRow - (size[numShip] - 1)>= 0)
			{
				emptyspace = checkSpaces.isEmpty(compBoard, letter, size, numShip, randomRow, randomCol, compD);

				if (emptyspace == true)
				{
					for (int x = 0; x < size[numShip]; x++)
					{
						compBoard[randomRow][randomCol] = letter[numShip];
						randomRow--; // decrement row for placement
						y++;
					}
					randomRow++;
					
				}
				else
				{
					randomRow = (rand() % ROWS);
					randomCol = (rand() % COLS);
				}
			}
			else
			{
				randomRow = (rand() % ROWS);
				randomCol = (rand() % COLS);
			}
		}
		else
		{
			if (randomRow  + (size[numShip] - 1) < ROWS)
			{
				emptyspace = checkSpaces.isEmpty(compBoard, letter, size, numShip, randomRow, randomCol, compD);

				if (emptyspace == true)
				{
					for (int x = 0; x < size[numShip]; x++)
					{
						compBoard[randomRow][randomCol] = letter[numShip]; 
						randomRow++; // increment row for placement
						y++;
					}
					randomRow--;
				}
				else
				{
					randomRow = (rand() % ROWS);
					randomCol = (rand() % COLS);
				}
			}
			else
			{
				randomRow = (rand() % ROWS);
				randomCol = (rand() % COLS);
			}
		}
	}
}

void Board::eastOrWest(string compBoard[ROWS][COLS], string letter[], int size[], int numShip,int d)
{
	Gameboard checkSpaces;

	// Random number generators for the randomRow and randomCol placement
	int randomRow = (rand() % ROWS);
	int randomCol = (rand() % COLS);
	bool emptyspace;
	int y = 0;

	// This loop executes until all spots have been filled based on ship size
	// First, it checks if random direction is East or West
	// Then, it checks if the ship will fit in the spot
	// Lastly, it will check if the spot it wants to place the ship is empty
	// If everything is good, the ship is placed and y incremented
	// Else, regenerates random nums and starts again
	while (y < size[numShip])
	{
		if (d == East)
		{
			if (randomCol + (size[numShip] - 1) < COLS) 
			{
				emptyspace = checkSpaces.isEmpty(compBoard, letter, size, numShip, randomRow, randomCol, d);

				if (emptyspace == true)
				{
					for (int x = 0; x < size[numShip]; x++)
					{
						// Couldn't figure out why below assignment gave warning. If you see this and have an explanation, please help
						// C6385: Reading invalid data from compBoard[R][C]: readable is 280 bytes but 308 could be read
						compBoard[randomRow][randomCol] = letter[numShip]; 
						randomCol++; // increments col for placement
						y++;
					}
					randomCol--;
				}
				else
				{
					randomRow = (rand() % ROWS);
					randomCol = (rand() % COLS);
				}
			}
			else
			{
				randomRow = (rand() % ROWS);
				randomCol = (rand() % COLS);
			}
		}
		else
		{
			if (randomCol - (size[numShip] - 1) >= 0)
			{
				emptyspace = checkSpaces.isEmpty(compBoard, letter, size, numShip, randomRow, randomCol, d);

				if (emptyspace == true)
				{
					for (int x = 0; x < size[numShip]; x++)
					{
						compBoard[randomRow][randomCol] = letter[numShip];
						randomCol--; // decrements Col for placement
						y++;
					}
					randomCol++;
				}
				else
				{
					randomRow = (rand() % ROWS);
					randomCol = (rand() % COLS);
				}
			}
			else
			{
				randomRow = (rand() % ROWS);
				randomCol = (rand() % COLS);
			}
		}
	}
}

void Board::printBoard(string compBoard[ROWS][COLS])
{
	// Prints out the board
	cout << "  0  1  2  3  4  5  6  7  8  9\n";
	for (int r = 0; r < ROWS; r++)
	{
		cout << r << " ";

		for (int c = 0; c < COLS; c++)
		{
			cout << compBoard[r][c] << "  ";
		}

		cout << endl;
	}
}
