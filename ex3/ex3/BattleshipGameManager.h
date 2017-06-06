#pragma once

#include "IBattleshipGameAlgo.h"
#include "Ship.h"
#include "BattleshipBoard.h"
#include <windows.h>
#include "GamePlayerData.h"

typedef IBattleshipGameAlgo *(*GetAlgoFuncType)();

class BattleshipGameManager
{

public:

	static const int PLAYERID_A = 0;														/* default id for player A */
	static const int PLAYERID_B = 1;														/* default id for player B */
	static const int UNDEFINED_PLAYERID = -1;												/* default id for undefined or invalid player */


	BattleshipGameManager(int argc, char* argv[]);											/* constructor */
	~BattleshipGameManager();

	BattleshipGameManager() = delete;														/* deletes empty constructor */
	BattleshipGameManager(const BattleshipGameManager& otherGame) = delete;					/* deletes copy constructor */
	BattleshipGameManager& operator=(const BattleshipGameManager& otherGame) = delete;		/* deletes assignment constructor */


	bool isGameSuccessfullyCreated()const { return gameSuccessfullyCreated; }				/* we will check the variable in the main */
	void Run();																				/* given a game object, run's the game and outputs the results */



private:

	static const char A = 'A';																/* player char for player A - for printing */
	static const char B = 'B';																/* player char for player B */
	static const int DEAFULT_BOARD_ROWS = 10;												/* default rows number for the main board */
	static const int DEAFULT_BOARD_COLS = 10;												/* default cols number for the main board */
	static const int NUM_OF_PLAYER_SHIPS = 5;												/* number of valid ships for each game player */


	std::vector<std::pair<int, HINSTANCE>> dll_vec;											/* vector of <playerID, dll handle> */

	GamePlayerData playerA;																	/* an object that keeps all relevant data of playerA in the game */
	GamePlayerData playerB;																	/* an object that keeps all relevant data of playerB in the game */

	IBattleshipGameAlgo* playerAlgoA;														/* pointer to the algo of playerA - will deleted in **this** class destructor */
	IBattleshipGameAlgo* playerAlgoB;														/* pointer to the algo of playerB - will deleted in **this** class destructor */





	std::string inputDirPath;
	std::string boardFilePath;

	BattleshipBoard mainBoard;
	bool gameSuccessfullyCreated;

	static void outputGameResult(GamePlayerData* currPlayer, GamePlayerData* otherPlayer);
	bool checkGameArguments(int argc, char* argv[]);
	bool checkGamefiles(std::string& boardPath, std::string& dllPathPlayerA, std::string& dllPathPlayerB);

	/* given a game main board, returns true if the board is valid according to the game rules:
	right number of valid ships for each player, no invalid and adjacent ships in board. */
	bool BattleshipGameManager::checkMainBoardValidity()const;

	/* given a matrix board for a specific player, returns number of valid ships and set of invalid ships letters (according to the game rules
	for example - <5, {'M', 'P'}> - input player board has 5 valid ships, but invalid size or shape 'M' and 'P' ships  */
	static std::pair<size_t, std::set<char>> FindNumberOfValidShipsInBoard(BattleshipBoard& board);

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

	void sendAttackForPrint(std::pair<int, int> nextAttack, AttackResult attackRes)const;
};
