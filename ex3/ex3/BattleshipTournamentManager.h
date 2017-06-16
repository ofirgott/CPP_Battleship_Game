#pragma once

#include "BattleshipBoard.h"
#include "PlayerAlgoDetails.h"
#include <queue> 
#include "BattleshipGameManager.h"
#include <mutex>
#include <atomic>
#include "PlayerGameResultData.h"
#include "SingleGameProperties.h"
#include "RoundData.h"


class BattleshipTournamentManager
{
public:
	BattleshipTournamentManager(int argc, char* argv[]);
	~BattleshipTournamentManager();
	BattleshipTournamentManager(const BattleshipTournamentManager& otherTournament) = delete;					/* deletes copy constructor */

	bool isTournamentSuccessfullyCreated()const { return successfullyCreated; }
	void RunTournament();

	
private:
	
	static const int TOURNAMENT_MIN_PLAYERS = 2;
	static const size_t DEFAULT_THREADS_NUM = 4;
	static const char A = 'A';																/* player char for player A - for printing */
	static const char B = 'B';																/* player char for player B */
	static const int PLAYERID_A = 0;
	static const int PLAYERID_B = 1;
	static const bool DEFAULT_PRINT_SINGLE_TABLE = false;
	size_t maxGamesThreads;
	bool successfullyCreated;
	std::string inputDirPath;

	std::vector<BattleshipBoard> boardsVec;
	std::vector<PlayerAlgoDetails> algosDetailsVec;
	
	

	std::queue<SingleGameProperties> gamesPropertiesQueue;
	std::vector<std::vector<PlayerGameResultData>> allGamesResults; // table: for each algo vector of his results
	std::vector<std::atomic<int>>playersProgress;
	std::vector<RoundData> allRoundsData;
	
	std::mutex gamesQueueMutex, isRoundDoneMutex;
	std::condition_variable isRoundDoneCondition;
	
	bool printSingleTable;
	

	std::vector<PlayerGameResultData> allRoundsCumulativeData;
	//int algosIndex;
	
	
	


	void createGamesPropertiesQueue();
	void singleThreadJob();
	void updateGamesResults(const PlayerGameResultData& currGameRes, const SingleGameProperties& gamsProperty);
	bool checkTournamentArguments(int argc, char* argv[]);
	bool checkTournamentBoards();
	
	/* given a game main board, returns true if the board is valid according to the game rules:
	right number of valid ships for each player, no invalid and adjacent ships in board. */
	static bool checkBoardValidity(const BattleshipBoard& board);
	
	/* given a matrix board for a specific player, returns number of valid ships and set of invalid ships letters (according to the game rules
	for example - <5, {'M', 'P'}> - input player board has 5 valid ships, but invalid size or shape 'M' and 'P' ships  */
	//TODO: FIX THE DUCO, IT IS NOW TRUE!!!!!
	static void FindValidAndInvalidShipsInBoard(const BattleshipBoard& board, std::set<std::pair<char, std::set<Coordinate>>>& validShips_A, std::set<char>& invalidShips_A, std::set<std::pair<char, std::set<Coordinate>>>& validShips_B, std::set<char>& invalidShips_B);

	/* given a set of sips details for player, this function deletes invalid ships from the set, according to the game rules */
	/* in addition, adds letters of deleted found invalid ships to the set invalidShips*/
	static void DeleteInvalidShipsDetailsEntryFromSet(std::set<std::pair<char, std::set<Coordinate>>>& setOfShipsDetails, std::set<char>& invalidShips);
	
	/* given a player name and set of invalid ships letter for this player , prints relevant error message to the log for each invalid ship in set */
	static void PrintWrongSizeOrShapeForShips(std::set<char>& invalidShipsSet, char playerChar);

	static void comparePlayersShips(std::set<std::pair<char, std::set<Coordinate>>>& validShips_A, std::set<std::pair<char, std::set<Coordinate>>>& validShips_B);
	
	bool loadTournamentAlgos();

	bool loadPlayerDll(const std::string& currDllFilename);
};
