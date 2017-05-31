#pragma once
#include <string>
#include "BattleshipBoard.h"


class BattleshipTournamentManager
{
public:
	BattleshipTournamentManager(int argc, char* argv[]);
	~BattleshipTournamentManager();




private:
	
	std::string inputDirPath;
	std::vector<BattleshipBoard> boardsVec;


};
