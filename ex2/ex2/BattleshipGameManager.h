#pragma once

#include "IBattleshipGameAlgo.h"
#include "Ship.h"
#include "BattleshipBoard.h"
#include "Constants.h"
#include <windows.h>
#include "GamePlayerData.h"

typedef IBattleshipGameAlgo *(*GetAlgoFuncType)();
//GetAlgoFuncType getShapeFunc;

/* todo: 1.change the run() function to access the mainBoard. 2. the constructor shoul init utilGamePlayer ang not ibattelship game algo*/
class BattleshipGameManager
{
	//friend class GamePlayerData;
public:
	
	BattleshipGameManager() = delete;														/* deletes empty constructor */
	BattleshipGameManager(const BattleshipGameManager& otherGame) = delete;					/* deletes copy constructor */	
	BattleshipGameManager& operator=(const BattleshipGameManager& otherGame) = delete;		/* deletes assignment constructor */

	BattleshipGameManager(int argc, char* argv[]);

	~BattleshipGameManager();
	

	bool isGameSuccessfullyCreated()const { return gameSuccessfullyCreated; }
	void Run();			/* given a game instance run's the game and outputs the results */

private:
	//friend class GamePlayerData;
	std::vector<std::pair<int, HINSTANCE>> dll_vec; // vector of <playerID, dll handle>

	GamePlayerData playerA;
	GamePlayerData playerB;
	
	std::string inputDirPath;
	std::string boardFilePath;
	
	BattleshipBoard mainBoard;
	bool gameSuccessfullyCreated;

	static void switchCurrPlayer(GamePlayerData** curr, GamePlayerData** other);
	static void outputGameResult(GamePlayerData* currPlayer, GamePlayerData* otherPlayer);
	bool checkGameArguments(int argc, char* argv[], bool& printFlag, int& printDelay);
	bool checkGamefiles(std::string& boardPath, std::string& dllPathPlayerA, std::string& dllPathPlayerB);
	
	/* given a game main board, returns true if the board is valid according to the game rules:
	right number of valid ships for each player, no invalid and adjacent ships in board. */
	bool BattleshipGameManager::checkMainBoardValidity()const;

	/* given a matrix board for a specific player, returns number of valid ships and set of invalid ships letters (according to the game rules
	for example - <5, {'M', 'P'}> - input player board has 5 valid ships, but invalid size or shape 'M' and 'P' ships  */
	std::pair<size_t, std::set<char>> FindNumberOfValidShipsInBoard(BattleshipBoard& board)const;

	/* given a set of sips details for player, this function deletes invalid ships from the set, according to the game rules */
	/* in addition, adds letters of deleted found invalid ships to the set invalidShips*/
	static void DeleteInvalidShipsDetailsEntryFromSet(std::set<std::pair<char, std::set<std::pair<int, int>>>>& setOfShipsDetails, std::set<char>& invalidShips);


	/* given a player name and set of invalid ships letter for this player , prints relevant error message for each invalid ship in set */
	static void PrintWrongSizeOrShapeForShips(std::set<char>& invalidShipsSet, char playerChar);

	/* given a player name and his set of valid ships, returns true if the player has NUM_OF_PLAYER_SHIPS valid ships,
	else prints relevant error message (for too many / too few ships), and returns false */
	static bool isCorrectNumberOfShipsForPlayer(size_t validShipsCnt, char playerChar);

	bool initGamePlayers(const std::string& dllPathPlayerA, const std::string& dllPathPlayerB);

	bool BattleshipGameManager::loadAndInitPlayerDll(const std::string & dllPathPlayer, IBattleshipGameAlgo* &player, int playerId, HINSTANCE& hDll, Ship*** &shipsMatrix, size_t& shipsCnt)const;
	
};
