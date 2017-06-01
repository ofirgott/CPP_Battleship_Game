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
	static const int TOURNAMENT_MIN_BOARDS = 1;
	
	std::string inputDirPath;
	std::vector<BattleshipBoard> boardsVec;
	std::vector<PlayerAlgoDetails> algosDetailsVec;
	bool successfullyCreated;

	bool checkTournamentArguments(int argc, char* argv[]);
	bool checkTournamentBoards();
	bool loadTournamentAlgos();
};
