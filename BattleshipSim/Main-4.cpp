#include "Gameboard.h"
#include "Board.h"
#include "Playerboard.h"
#include "Ship.h"
#include "Windows.h"


int main()
{

StartOver:

	// To seed random number generator
	srand((unsigned int)time(NULL));

	// Create boards
	const int numberOfShips = 5;
	const int ROWS = 10;
	const int COLS = 10;
	string playerBoard[ROWS][COLS];
	string enemyBoard[ROWS][COLS];
	string attackBoard[ROWS][COLS];
	string playerName;
	bool exitGame = false;
	int messageOutCount = -5; // To get direction during placement and bypass rest of game; also doubles as game counter
	int userRow;
	int userCol;
	int userDirection;
	string* namePtr = nullptr;
	string* letterPtr = nullptr;
	int* sizePtr = nullptr;
	int* userRowPtr = nullptr;
	int* userColPtr = nullptr;
	int* userDirPtr = nullptr;

	// Objects initialized for program
	Gameboard gameBoardSetUp, moves, battlefieldPrint;
	Playerboard playerBoardSetup, getInput;
	Board enemyBoardSetup;
	Ship frigate, sub, destroyer, battleship, aircraftCarrier, playerShips;

	// Sets ship sizes, names, and their letters
	frigate.setShipSize(2), frigate.setShipLetter("F"), frigate.setShipName("Frigate");
	sub.setShipSize(3), sub.setShipLetter("S"),sub.setShipName("Submarine");
	destroyer.setShipSize(3), destroyer.setShipLetter("D"), destroyer.setShipName("Destroyer");
	battleship.setShipSize(4), battleship.setShipLetter("B"), battleship.setShipName("Battleship");
	aircraftCarrier.setShipSize(5), aircraftCarrier.setShipLetter("A"), aircraftCarrier.setShipName("Aircraft Carrier");

	int shipSize[5] = { frigate.getShipSize(), sub.getShipSize(), destroyer.getShipSize(), battleship.getShipSize(), aircraftCarrier.getShipSize() };
	string shipLetter[5] = { frigate.getShipLetter(), sub.getShipLetter(), destroyer.getShipLetter(), battleship.getShipLetter(), aircraftCarrier.getShipLetter() };
	string shipName[5] = { frigate.getShipName(), sub.getShipName(), destroyer.getShipName(), battleship.getShipName(), aircraftCarrier.getShipName() };

	// Pointers
	namePtr = shipName;
	letterPtr = shipLetter;
	sizePtr = shipSize;
	userRowPtr = &userRow;
	userColPtr = &userCol;
	userDirPtr = &userDirection;
	
	// INITIALIZING GAME BOARDS AND PRINT INTRO MESSAGE
	gameBoardSetUp.createBoard(enemyBoard, playerBoard, attackBoard);
	gameBoardSetUp.introMessage(1);

	cout << "---------- RULES -----------\n";
	cout << "The first to find all ships or miss 15 consecutive shots risks losing everything!\n\n";
	cout << "First things first... what is your name? ";
	cin >> playerName;
	cout << "\nThank you " << playerName << "!\n\n";
	cout << "Entering Ship Placement Phase. Ready your vessels for battle!\n";

	string winner;
	int shipCounter = 0;
	int maxMoves = 15;
	int movesLeft = maxMoves;
	int playerNumGen = rand() % (4 - 1) + 1;
	int player1 = 1;
	
	// To generate who goes first
	player1 = playerNumGen;

	while (shipCounter < numberOfShips) 
	{
		// This prints the player board and prints out ship info
		// For each ship the user must place, it displays the name, ship size, and ship letter
		gameBoardSetUp.printPlayerBoard(playerBoard, playerName);
		playerShips.createUserShips(namePtr, sizePtr, letterPtr, shipCounter);

	NoSpace:
		exitGame = getInput.getUserInput(userRowPtr, userColPtr, userDirPtr);
		if (exitGame == true && messageOutCount != 1)
		{
			goto GameEnd;
		}

		// The program checks for an empty space for the ship the user wants to place
		// If the spot is not empty, it will return an error message letting the user know
		// why their ship could not be placed there
		// Otherwise, the ship will be placed and ship counter incremented
		string collision = "col";
		string endOfWorld = "end";

		userDirection = playerBoardSetup.chooseDirection(userDirPtr, messageOutCount);
		
		string noSpace = playerBoardSetup.placeShips(playerBoard, shipCounter, userRowPtr, userColPtr, userDirPtr);
		if (noSpace == "col")
		{
			cout << "\nWARNING: A ship is already here!";
			goto NoSpace;
		}
		if (noSpace == "end")
		{
			cout << "\nCAUTION: You're sailing off of the map!";
			goto NoSpace;
		}

		shipCounter++;
	}

	// Populates enemy board
	enemyBoardSetup.populateCompBoard(enemyBoard, shipLetter, shipSize, numberOfShips);
	
	if (exitGame != true)
	{
		Sleep(2000);
		cout << "\n\n\n\nLet the battle begin!\n\n";
		Sleep(2500);
	}
	if (player1 == 1)
	{
		cout << "\nYour crew got to the cannons first!\n";
	}
	// This block begins the game phase. It starts with a random number to determine who is the first player
	// After doing so, it will execute the appropriate moves
	// If the user misses 15 moves in a row, the game will end
	while (exitGame != true && movesLeft > 0)
	{
		// Logic for determining who goes first
		// If player1 random number picks 1, then the user will go first
		// Else, the computer goes first
		if (player1 == 1)
		{
			cout << "\nReady to fire!\n";
			// Prints the blank board for the player, receives input, checks if the space is a hit/miss/invalid, and prints out the attack board to see the result
			gameBoardSetUp.printAttackBoard(attackBoard);
			cout << "Moves Left: " << movesLeft;
			exitGame = getInput.attackInput(userRowPtr, userColPtr);
			if (exitGame == true)
			{
				goto GameEnd;
			}

			exitGame = moves.playerAttack(enemyBoard, attackBoard, userRow, userCol, player1);
			if (exitGame == true)
			{
				goto GameEnd;
			}
			else if (enemyBoard[userRow][userCol] == "X")
			{
				movesLeft = maxMoves;
			}
			else
			{
				movesLeft--;
				if (movesLeft == 0)
				{
					winner = "MOVES";
					goto GameEnd;
				}
			}

			exitGame = moves.checkBattlefield(enemyBoard, playerBoard);
			if (exitGame == true)
			{
				winner = "WINNER";
				goto GameEnd;
			}
			gameBoardSetUp.printAttackBoard(attackBoard);

			// Program pauses for 1 second and lets the computer retaliate 
			Sleep(2500);
			cout << "\nThe enemy is winding up!\n";
			Sleep(2500);

			// Enemy should attack, the player board will print out, and the game will both boards to see if all ships were found
			moves.enemyAttack(playerBoard);
			Sleep(2500);
			exitGame = moves.checkBattlefield(enemyBoard, playerBoard);
			if (exitGame == true)
			{
				winner = "LOSER";
				goto GameEnd;
			}
			gameBoardSetUp.printPlayerBoard(playerBoard, playerName);
		}
		else
		{
			// Computer moves first and user second
			cout << "\nYou hear a loud noise and see something flying towards you...\n";
			Sleep(2500);

			// Enemy should attack, the player board will print out, and the game will both boards to see if all ships were found
			moves.enemyAttack(playerBoard);

			exitGame = moves.checkBattlefield(enemyBoard, playerBoard);
			if (exitGame == true)
			{
				winner = "LOSER";
				goto GameEnd;
			}
			gameBoardSetUp.printPlayerBoard(playerBoard, playerName);
			
			Sleep(2500);
			// Player move
			cout << "\nYour turn at the helm\n";
			Sleep(2500);

			gameBoardSetUp.printAttackBoard(attackBoard);
			cout << "Moves Left: " << movesLeft << "\n";

			// If user enters the sentinel, end the game
			// Else if either board has all ships found
			// Else, exit game
			exitGame = getInput.attackInput(userRowPtr, userColPtr);
			exitGame = moves.playerAttack(enemyBoard, attackBoard, userRow, userCol, player1);
			if (exitGame == true)
			{
				goto GameEnd;
			}
			if (enemyBoard[userRow][userCol] == "X")
			{
				movesLeft = maxMoves;
			}
			else
			{
				movesLeft--;
				if (movesLeft == 0)
				{
					winner = "MOVES";
					goto GameEnd;
				}
			}

			exitGame = moves.checkBattlefield(enemyBoard, playerBoard);
			if (exitGame == true)
			{
				winner = "WINNER";
				goto GameEnd;
			}
			
			gameBoardSetUp.printAttackBoard(attackBoard);
		}
	}
GameEnd:
	string playAgain;
	battlefieldPrint.printBattlefield(enemyBoard, playerBoard, playerName);
	if (winner == "WINNER")
	{
		cout << "\nYou have sunk all of the enemy battleships! Play again? Y/N\n";
	}
	else if (winner == "LOSER")
	{
		cout << "\nThe enemy has sunk all of your battleships! Play again? Y/N\n";
	}
	else if (winner == "MOVES")
	{
		cout << "\nYou have ran out of moves! Play again? Y/N\n";
	}
	else
	{
		cout << "\nGAME OVER. Play again? Y/N\n";
	}
	cin >> playAgain;
	
	if (playAgain == "Y" || playAgain == "y")
	{
		cout << "\n";
		goto StartOver;
	}
	

	return 0;
}
