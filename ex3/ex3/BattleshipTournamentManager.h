#pragma once
#include <string>
#include "BattleshipBoard.h"
#include "PlayerAlgoDetails.h"
#include <queue> 
#include "BattleshipGameManager.h"
#include <thread>
#include <mutex>
#include <atomic>
#include "StandingsTableEntryData.h"
#include "SingleGameProperties.h"
#include "BattleshipPrint.h"

//todo: move it to seperate file
struct Round
{

	//int roundNumber;
	std::atomic<size_t> numOfPlayersLeft;
	bool status;
	//std::mutex 
	//Round() : roundNumber(0), status(false){ numOfGamesLeft.store(0); }
	//Round() : status(false) { numOfGamesLeft.store(0); }
	Round() : status(false) { }
	//Round(int rNum, int atom, bool s) : roundNumber(rNum), status(s){ numOfGamesLeft.store(0); }
	Round(size_t numOfPlayers, bool s) : status(s) { numOfPlayersLeft.store(numOfPlayers); }

	//explicit Round(const Round& round) : roundNumber(round.roundNumber), status(round.status) { numOfGamesLeft.store(round.numOfGamesLeft.load()); }			/* copy constructor */
	explicit Round(const Round& round) = delete;
	 Round(Round&& round) noexcept : status(round.status) { numOfPlayersLeft.store(round.numOfPlayersLeft.load()); }
	//Round& operator=(Round& round) { roundNumber = round.roundNumber; numOfGamesLeft.store(round.numOfGamesLeft.load());  status = round.status; return *this; }								/* delete copy assignment */
};

class BattleshipTournamentManager
{
public:
	BattleshipTournamentManager(int argc, char* argv[]);
	~BattleshipTournamentManager();

	bool isTournamentSuccessfullyCreated()const { return successfullyCreated; }
	void RunTournament();

	
private:

	static const int TOURNAMENT_MIN_PLAYERS = 2;
	static const size_t DEFAULT_THREADS_NUM = 4;			/* TODO: we want to load it from the config file for the bonus! need to think about nore parameters that we want to load from there*/
	static const char A = 'A';																/* player char for player A - for printing */
	static const char B = 'B';																/* player char for player B */
	static const int PLAYERID_A = 0;
	static const int PLAYERID_B = 1;

	std::string inputDirPath;
	std::vector<BattleshipBoard> boardsVec;
	std::vector<PlayerAlgoDetails> algosDetailsVec;
	size_t maxGamesThreads;
	bool successfullyCreated;

	//diana and sharon adds
	//std::vector<std::thread> threadsPool;	//Ofir: maybe delete from here because of - https://stackoverflow.com/questions/40770913/c-threading-no-instance-of-constructor-stdthreadthread-matches-the-a
	std::queue<SingleGameProperties> gamesPropertiesQueue;
	std::mutex gamesQueueMutex;
	std::condition_variable queueEmptyCondition;
	std::vector<std::vector<StandingsTableEntryData>> allGamesResults; // table: for each algo vector of his results
	std::vector<std::atomic<int>>playersProgress;
	std::vector<Round> allRounds;
	std::vector<StandingsTableEntryData> RoundDataToPrint;
	int algosIndex;

	std::condition_variable isRoundDoneCondition;
	std::mutex isRoundDoneMutex;

	void createGamesPropertiesQueue();
	void singleThreadJob();
	void updateAllGamesResults(const StandingsTableEntryData& currGameRes, const SingleGameProperties& gamsProperty);
		
	//diana and sharon adds



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

	void loadPlayerDll(const std::string& currDllFilename);
};
