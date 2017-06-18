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
#include "Logger.h"


class BattleshipTournamentManager
{
public:
	BattleshipTournamentManager(int argc, char* argv[]);
	~BattleshipTournamentManager();
	BattleshipTournamentManager(const BattleshipTournamentManager& otherTournament) = delete;					/* deletes copy constructor */

	bool isTournamentSuccessfullyCreated()const { return successfullyCreated; }
	void RunTournament();

private:
	
	static const int TOURNAMENT_MIN_PLAYERS_DEFAULT = 2;
	static const size_t DEFAULT_THREADS_NUM = 4;
	static const bool PRINT_SINGLE_TABLE = false;
	static const char A = 'A';																/* player char for player A - for printing */
	static const char B = 'B';																/* player char for player B */
	static const int PLAYERID_A = 0;
	static const int PLAYERID_B = 1;
	static const std::string LOG_FILENAME;
	static const int UNINITIALIZED_ARG = -1;
	
	
	size_t maxGamesThreads;
	bool successfullyCreated;
	std::string inputDirPath;
	std::vector<BattleshipBoard> boardsVec;												
	std::vector<PlayerAlgoDetails> algosDetailsVec;
	std::queue<SingleGameProperties> gamesPropertiesQueue;									/* tournament games queue */
	std::vector<std::vector<PlayerGameResultData>> allGamesResults;							/* maintains for each player his games results for every round */	
	std::vector<std::atomic<int>>playersProgress;											/* maintains for every player in which round he is (atomic, and therefore thread safe) */
	std::vector<RoundData> allRoundsData;													/* maintains the status for every round in the game, to check if specific round is done */			
	
	std::mutex gamesQueueMutex, isRoundDoneMutex;					/* gameQueueMutex - to touch the games queue, isRoundDoneMutex - to know when round is really done */
	std::condition_variable isRoundDoneCondition;					/* to know excactly when round is done and prnt data */
	
	bool printSingleTable;											/* maintins the print method we want */

	std::vector<PlayerGameResultData> allRoundsCumulativeData;		/* for tables printing - data for each player in the tournament for the current round */
	
	int TOURNAMENT_MIN_PLAYERS;										/* in order to check if we have enough player for the tournament */
	LogLevel logLevelVal;

	void createGamesPropertiesQueue();
	
	/*  takes single game properties from the gamesQueue, run the game and then updae it's results */
	void singleThreadJob();
	
	/* given a single game results, update the data in the data structures */
	void updateGamesResults(const PlayerGameResultData& currGameRes, int playerIndexA, int playerIndexB);
	
	/* parse tournament input arguments*/
	bool checkTournamentArguments(int argc, char* argv[]);
	
	bool checkTournamentBoards();
	
	/* given a game main board, returns true if the board is valid according to the game rules */
	static bool checkBoardValidity(const BattleshipBoard& board);
	
	/* given a main board, update the input sets refernces with the valid and invalid ship details [for player A and B] */
	static void FindValidAndInvalidShipsInBoard(const BattleshipBoard& board, std::set<std::pair<char, std::set<Coordinate>>>& validShips_A, std::set<char>& invalidShips_A, std::set<std::pair<char, std::set<Coordinate>>>& validShips_B, std::set<char>& invalidShips_B);

	/* given a set of sips details for player, this function deletes invalid ships from the set, according to the game rules */
	/* in addition, adds letters of deleted found invalid ships to the set invalidShips*/
	static void DeleteInvalidShipsDetailsEntryFromSet(std::set<std::pair<char, std::set<Coordinate>>>& setOfShipsDetails, std::set<char>& invalidShips);
	
	/* given a player name and set of invalid ships letter for this player , prints relevant error message to the log for each invalid ship in set */
	static void PrintWrongSizeOrShapeForShips(std::set<char>& invalidShipsSet, char playerChar);

	/* checks if the board is balanced with number and type of the 2 players*/
	static void comparePlayersShips(std::set<std::pair<char, std::set<Coordinate>>>& validShips_A, std::set<std::pair<char, std::set<Coordinate>>>& validShips_B);
	
	/* fills the tournament algos vectors with valid algos from the input dir */
	bool loadTournamentAlgos();
	
	bool loadPlayerDll(const std::string& currDllFilename);

	void parseDefaultsFromConfigFile();
	void storeConfigLine(const std::string& key, const std::string& value);
	void printRouondGameResToLog(int currRound) const;
	void printProgramValuesToLog()const;
};
