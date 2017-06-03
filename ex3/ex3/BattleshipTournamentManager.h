#pragma once
#include <string>
#include "BattleshipBoard.h"
#include "PlayerAlgoDetails.h"


class BattleshipTournamentManager
{
public:
	BattleshipTournamentManager(int argc, char* argv[]);
	~BattleshipTournamentManager();




private:

	static const int TOURNAMENT_MIN_PLAYERS = 2;
	static const int DEFAULT_THREADS_NUM = 4;			/* TODO: we want to load it drim the config file for the bonus! need to think about nore parameters that we want to load from there*/
	static const char A = 'A';																/* player char for player A - for printing */
	static const char B = 'B';																/* player char for player B */
	static const int PLAYERID_A = 0;
	static const int PLAYERID_B = 1;

	std::string inputDirPath;
	std::vector<BattleshipBoard> boardsVec;
	std::vector<PlayerAlgoDetails> algosDetailsVec;
	int maxGamesThreads;
	bool successfullyCreated;


	bool checkTournamentArguments(int argc, char* argv[]);
	bool checkTournamentBoards();
	
	/* given a game main board, returns true if the board is valid according to the game rules:
	right number of valid ships for each player, no invalid and adjacent ships in board. */
	static bool checkBoardValidity(const BattleshipBoard& board);
	
	/* given a matrix board for a specific player, returns number of valid ships and set of invalid ships letters (according to the game rules
	for example - <5, {'M', 'P'}> - input player board has 5 valid ships, but invalid size or shape 'M' and 'P' ships  */
	//TODO: FIX THE DUCO, IT IS NOW TRUE!!!!!
	static void BattleshipTournamentManager::FindValidAndInvalidShipsInBoard(const BattleshipBoard& board, std::set<std::pair<char, std::set<Coordinate>>>& validShips_A, std::set<char>& invalidShips_A, std::set<std::pair<char, std::set<Coordinate>>>& validShips_B, std::set<char>& invalidShips_B);

	/* given a set of sips details for player, this function deletes invalid ships from the set, according to the game rules */
	/* in addition, adds letters of deleted found invalid ships to the set invalidShips*/
	static void DeleteInvalidShipsDetailsEntryFromSet(std::set<std::pair<char, std::set<Coordinate>>>& setOfShipsDetails, std::set<char>& invalidShips);
	
	/* given a player name and set of invalid ships letter for this player , prints relevant error message to the log for each invalid ship in set */
	static void PrintWrongSizeOrShapeForShips(std::set<char>& invalidShipsSet, char playerChar);

	static void comparePlayersShips(std::set<std::pair<char, std::set<Coordinate>>> validShips_A, std::set<std::pair<char, std::set<Coordinate>>> validShips_B);
	
	bool loadTournamentAlgos();

	void loadPlayerDll(const std::string& currDllFilename);
};
