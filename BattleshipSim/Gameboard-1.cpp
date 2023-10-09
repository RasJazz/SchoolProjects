#include "Gameboard.h"
#include "Board.h"
#include "Playerboard.h"
#include "Ship.h"
#include "Windows.h"


void Gameboard::introMessage(int start)
{
	cout << "The year is 2166. Due to the rapidly melting ice caps, local militias have begun an arms race over naval ships.\n";
	Sleep(2000);
	cout << "You, as a newly found Captain, have been exploring the seas to conquer Naval fleets taken over by rivalring factions.\n";
	Sleep(2000);
	cout << "Your goal is to annihilate your closest enemy to gain more soldiers in your fight to expand your arsenal.\n\n";
	Sleep(2000);
	cout << "While scouring the seas with your fleet, you hear the shouts of men... too distant to be your own.\n";
	Sleep(2000);
	cout << "\"GET CLOSER!!!\" you cry. The ship lets out a deep, gutteral groan and starts to change direction.\n";
	Sleep(2000);
	cout << "As your vessel cuts through the fog, you see a familiar fleet.\n";
	Sleep(2000);
	cout << "\"I know that banner from a mile away...\" you mutter under your breath. Some of your crew run down below.\n";
	Sleep(2000);
	cout << "Hopefully they get to the cannons before your enemy does...\n\n";
	Sleep(2000);

}

void Gameboard::createBoard(string enemyBoard[ROWS][COLS], string playerBoard[ROWS][COLS], string attackBoard[ROWS][COLS])
{
	string ocean = "-";
	// Initializes the empty arrays
	for (int r = 0; r < ROWS; r++)
	{
		for (int c = 0; c < COLS; c++)
		{
			attackBoard[r][c] = ocean;
			enemyBoard[r][c] = ocean;
			playerBoard[r][c] = ocean;
		}
	}
}

bool Gameboard::isEmpty(string gameBoard[ROWS][COLS], string letter[], int size[], int numShip, int r, int c, int d)
{
	string emptySpace = gameBoard[r][c];

	for (int x = 0; x < size[numShip] - 1; x++)
	{
		// If first space isn't empty, returns false
		if (emptySpace != "-")
		{
			return false;
		}
		else
		{
			// If vertical placement, decrements row
			if (d == North)
			{
				gameBoard[r--][c];
				emptySpace = gameBoard[r][c];
			}
			// If horizontal placement, increments col 
			else if (d == East)
			{
				gameBoard[r][c++];
				emptySpace = gameBoard[r][c];
			}
			// If vertical placement, increments row
			else if (d == South)
			{
				gameBoard[r++][c];
				emptySpace = gameBoard[r][c];
			}
			// If horizontal placement, decrements col
			else
			{
				gameBoard[r][c--];
				emptySpace = gameBoard[r][c];
			}
		}
	}
	// If last current space isn't empty, returns false
	if (emptySpace != "-")
	{
		return false;
	}

	return true;
}

bool Gameboard::playerAttack(string enemyBoard[ROWS][COLS], string attackBoard[ROWS][COLS], int fireRow, int fireCol, int player)
{
	Playerboard input;
	bool exitGame = false;
	string HIT = "X";
	string MISS = "O";
	string shipName;
	int* userRow = nullptr;
	int* userCol = nullptr;
	userRow = &fireRow;
	userCol = &fireCol;
	
	// First checks if the spot chosen was a hit or a miss; if so, asks user to refire
	// If spot chosen wasn't fired upon, returns to game; else, if user typed sentinel, returns true and ends the game
	// Else, if spot has a ship, marks the spot as a hit with text letting user know they hit
	// Else if miss, marks spot as a miss letting user know they missed
	HitShip:
	if (enemyBoard[fireRow][fireCol] != "-")
	{
		if (enemyBoard[fireRow][fireCol] == HIT || enemyBoard[fireRow][fireCol] == MISS)
		{
			cout << "\nYou already fired there. Try again!"; 
			exitGame = input.attackInput(userRow, userCol);
			if (exitGame == false)
			{
				goto HitShip;
			}
			else
			{
				return true;
			}
		}
		else
		{
			enemyBoard[fireRow][fireCol] = HIT;
			attackBoard[fireRow][fireCol] = HIT;
			cout << "\nYou have damaged their ship!\n";
			Sleep(2500);
		}
	}
	else
	{
		enemyBoard[fireRow][fireCol] = MISS;
		attackBoard[fireRow][fireCol] = MISS;
		cout << "\nNothing but ocean...\n";
		Sleep(2500);
	}
	return false;
}

void Gameboard::enemyAttack(string playerBoard[ROWS][COLS])
{
	string HIT = "X";
	string MISS = "O";
	string shipName;
	int hitRow = (rand() % ROWS);
	int hitCol = (rand() % COLS);
	int counter = 1;

	// First checks if the spot chosen was a hit or a miss; if so, lets user know computer is refiring
	// Else, if spot has a ship, marks the spot as a hit and lets user know computer hit their ship
	// Else if miss, marks spot as a miss and lets user know comp missed
	Reroll:
	if (playerBoard[hitRow][hitCol] != "-")
	{
		if (playerBoard[hitRow][hitCol] == HIT || playerBoard[hitRow][hitCol] == MISS)
		{
			cout << "\nThe enemy missed. Refiring!\n";
			hitRow = (rand() % ROWS);
			hitCol = (rand() % COLS);
			Sleep(500);
			goto Reroll;
		}
		else
		{
			playerBoard[hitRow][hitCol] = HIT;
			cout << "\nWith a loud BOOM! a cannonball rattles one of your ships...\n";
			Sleep(2500);
		}
	}
	else
	{
		playerBoard[hitRow][hitCol] = MISS;
		cout << "\n*SPLASH* ... The cannonball fell short and hit the water. You are fortunate that this fog is thick!\n";
		Sleep(2500);
	}
}

bool Gameboard::checkBattlefield(string enemyBoard[ROWS][COLS], string playerBoard[ROWS][COLS])
{
	Ship frigate, sub, destroyer, battleship, aircraftCarrier;
	frigate.setShipSize(2), sub.setShipSize(3), destroyer.setShipSize(3), battleship.setShipSize(4), aircraftCarrier.setShipSize(5);
	int shipSize[5] = { frigate.getShipSize(), sub.getShipSize(), destroyer.getShipSize(), battleship.getShipSize(), aircraftCarrier.getShipSize() };
	string HIT = "X";
	string MISS = "O";
	int playerHitCounter = 0;
	int enemyHitCounter = 0;
	int totalShipSize = 0;

	// Sets the totalShipSize to the total length of all ships
	// Checks both boards to find a hit marker
	// If a hit is found, the appropriate counter is incremented
	// Once either counter hits length 17, the program ends the game
	for (int x = 0; x < numberOfShips; x++)
	{
		totalShipSize += shipSize[x];
	}

	for (int r = 0; r < ROWS; r++)
	{
		for (int c = 0; c < COLS; c++)
		{
			if (playerBoard[r][c] == HIT)
			{
				playerHitCounter++;
			}
			if (enemyBoard[r][c] == HIT)
			{
				enemyHitCounter++;
			}
		}
	}

	if (playerHitCounter == totalShipSize || enemyHitCounter == totalShipSize)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Gameboard::printPlayerBoard(string playerBoard[ROWS][COLS], string name)
{
	cout << "\n" << name << "'s Board\n";
	cout << "  0  1  2  3  4  5  6  7  8  9\n";

	for (int r = 0; r < ROWS; r++)
	{
		cout << r << " ";

		for (int c = 0; c < COLS; c++)
		{
			cout << playerBoard[r][c] << "  ";
		}
		cout << endl;
	}
}

void Gameboard::printAttackBoard(string attackBoard[ROWS][COLS])
{
	cout << "\nEnemy Board\n";
	cout << "  0  1  2  3  4  5  6  7  8  9\n";
	for (int r = 0; r < ROWS; r++)
	{
		cout << r << " ";

		for (int c = 0; c < COLS; c++)
		{
			cout << attackBoard[r][c] << "  ";
		}

		cout << endl;
	}
}

void Gameboard::printBattlefield(string enemyBoard[ROWS][COLS], string playerBoard[ROWS][COLS], string name)
{
	cout << "\n" << name << "'s Board\n";
	cout << "  0  1  2  3  4  5  6  7  8  9\n";

	for (int r = 0; r < ROWS; r++)
	{
		cout << r << " ";

		for (int c = 0; c < COLS; c++)
		{
			cout << playerBoard[r][c] << "  ";

		}

		cout << endl;
	}
	// Prints out the regular board

	Sleep(300);

	cout << "\nEnemy Board\n";
	cout << "  0  1  2  3  4  5  6  7  8  9\n";


	for (int r = 0; r < ROWS; r++)
	{
		cout << r << " ";

		for (int c = 0; c < COLS; c++)
		{
			cout << enemyBoard[r][c] << "  ";
		}

		cout << endl;
	}
}
