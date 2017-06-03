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
	
	std::string inputDirPath;
	std::vector<BattleshipBoard> boardsVec;
	std::vector<PlayerAlgoDetails> algosDetailsVec;
	int maxGamesThreads;
	bool successfullyCreated;


	bool checkTournamentArguments(int argc, char* argv[]);
	bool checkTournamentBoards();
	
	/* given a game main board, returns true if the board is valid according to the game rules:
	right number of valid ships for each player, no invalid and adjacent ships in board. */
	bool checkBoardValidity(const BattleshipBoard& board)const;
	
	bool loadTournamentAlgos();
};
