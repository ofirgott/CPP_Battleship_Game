#pragma once

#include "IBattleshipGameAlgo.h"
#include "Ship.h"
#include "BattleshipBoard.h"
#include "Constants.h"
#include <windows.h>

typedef IBattleshipGameAlgo *(*GetAlgoFuncType)();
//GetAlgoFuncType getShapeFunc;

class BattleshipGameManager
{
	/*keep all current algo details*/
	class UtilGamePlayer {
		friend class BattleshipGameManager;
	private:
		int id;
		IBattleshipGameAlgo* playerAlgo;
		bool hasMoreMoves;
		int score;
		Ship*** shipsMatrix;
		int currShipsCount;

		UtilGamePlayer() : id(-1), playerAlgo(nullptr), hasMoreMoves(true), score(0), shipsMatrix(nullptr), currShipsCount(0) {}
		UtilGamePlayer(int playerID, IBattleshipGameAlgo* inputPlayerAlgo, Ship*** inputShipsMatrix, int shipsCount) : id(playerID), playerAlgo(inputPlayerAlgo), hasMoreMoves(true), score(0), shipsMatrix(inputShipsMatrix), currShipsCount(shipsCount){}

		~UtilGamePlayer()
		{
			// todo: free the ship matrix here		
		}
		/*get next valid attack coordinates,if player doesnt have more moves return <-1,-1>*/
		std::pair<int, int> getAlgoNextAttack() const;
		
		/* given coordinates  player updates number of ships he has got left&& updates the attack in his ships details.
		   return the attack result and the number of pointes the attack scored
			if player attacked the same coordinate in the second time return <Hit, -1> to indicate that the player shoudnt keep his turn
		*/
		std::pair<AttackResult, int> realAttack(std::pair<int, int> coor);
		
		/* update players score to the prev score + num
			assume- num >= 0
		*/
		void incrementScore(int value) { score += value; }
		
	};


public:
	
	BattleshipGameManager() = delete;														/* deletes empty constructor */
	BattleshipGameManager(const BattleshipGameManager& otherGame) = delete;					/* deletes copy constructor */	
	BattleshipGameManager& operator=(const BattleshipGameManager& otherGame) = delete;		/* deletes assignment constructor */

	BattleshipGameManager(int argc, char* argv[]);
	
	/*	isGameSuccessfullyCreated - true if constructor succeded, false otherwise
	boardPath- path to the location of the game board
	*/
	BattleshipGameManager(std::string boardPath, bool& isGameSuccessfullyCreated);

	~BattleshipGameManager();

	bool isGameSuccessfullyCreated()const { return gameSuccessfullyCreated; }
	void Run() const;			/* given a game instance run's the game and outputs the results */

private:

	std::vector<std::tuple<int, HINSTANCE, GetAlgoFuncType>> dll_vec; // vector of <playerID, dll handle, GetAlgorithm function ptr>

	UtilGamePlayer* playerA;
	UtilGamePlayer* playerB;
	
	std::string inputDirPath;
	std::string boardFilePath;
	
	BattleshipBoard mainBoard;
	bool gameSuccessfullyCreated;

	static void switchCurrPlayer(UtilGamePlayer** curr, UtilGamePlayer** other);
	static void outputGameResult(UtilGamePlayer* currPlayer, UtilGamePlayer* otherPlayer);
	bool checkGameArguments(int argc, char* argv[], bool& printFlag, int& printDelay);
	bool checkGamefiles(std::string& boardPath, std::string& dllPathPlayerA, std::string& dllPathPlayerB);
	
	/* given a game main board, returns true if the board is valid according to the game rules:
	right number of valid ships for each player, no invalid and adjacent ships in board. */
	bool BattleshipGameManager::checkMainBoardValidity()const;

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

	bool initGamePlayers(const std::string& dllPathPlayerA, const std::string& dllPathPlayerB);

	bool BattleshipGameManager::loadAndInitPlayerDll(const std::string & dllPathPlayer, IBattleshipGameAlgo* player, int playerId, HINSTANCE& hDll);
	
};
