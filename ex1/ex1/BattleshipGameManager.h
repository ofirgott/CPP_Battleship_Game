#pragma once
#include "BattleshipBoard.h"
#include "Player.h"
#include "Constants.h"
#include <set>



class BattleshipGameManager
{
public:
	//BattleshipGameManager() : boardFilePath(), attackFilePath_A(), attackFilePath_B(), mainBoard(BattleshipBoard()), playerA(), playerB(), currPlayer(), otherPlayer() {};	//todo: if work without it, delete!
	BattleshipGameManager(std::string boardPath, std::string attackFilePath_a, std::string attackFilePath_b, bool& isGameSuccessfullyCreated);
	
	~BattleshipGameManager() {};
	
	BattleshipGameManager(const BattleshipGameManager& otherGame) = delete;					/* removes the copy constructor */
	
	BattleshipGameManager& operator=(const BattleshipGameManager& otherGame) = delete;		/* and also the assignment operator - we want game to be a Non Copyable object */

	void Run();


private:

	std::string boardFilePath;
	std::string attackFilePath_A;
	std::string attackFilePath_B;
	BattleshipBoard mainBoard;			/* main board object - in specific game we will have only one instance of it - frm this we will produce the players boards */
	Player playerA;
	Player playerB;
	Player* currPlayer;				/* pointers to players to know which player has the turn */
	Player* otherPlayer;

	char** GetCopyOfBoard()const { return mainBoard.GetCopyOfBoard(); };		/* returns matrix **copy** of the main board */


	/* given a game main board, returns true if the board is valid according to the game rules:
	   right number of valid ships for each player, no invalid and adjacent ships in board. */
	bool checkBoardValidity(const BattleshipBoard& board);						
																				
	
	/* given a matrix board for a specific player, returns number of valid ships and set of invalid ships letters (according to the game rules
	   for example - <5, {'M', 'P'}> - input player board has 5 valid ships, but invalid size or shape 'M' and 'P' ships  */
	static std::pair<size_t, std::set<char>> FindNumberOfValidShipsInBoard(const char** board, int rows, int cols);


	/* given a set of sips details for player, this function deletes invalid ships from the set, according to the game rules */
	/* in addition, adds letters of deleted found invalid ships to the set invalidShips*/
	static void DeleteInvalidShipsDetailsEntryFromSet(std::set<std::pair<char, std::set<std::pair<int, int>>>>& setOfShipsDetails, std::set<char>& invalidShips);


	/* given a player name and set of invalid ships letter for this player , prints relevant error message for each invalid ship in set */
	static void PrintWrongSizeOrShapeForShips(std::set<char>& invalidShipsSet, char playerChar);

	/* given a player name and his set of valid ships, returns true if the player has NUM_OF_PLAYER_SHIPS valid ships,
	   else prints relevant error message (for too many / too few ships), and returns false */
	static bool isCorrectNumberOfShipsForPlayer(size_t validShipsCnt, char playerChar);

	void updateCurrPlayer();		/* utility function for Run, switches currentPlayer with otherPlayer pointers */
	
	void outputGameResult()const;		/* prints end of game messages */

};
