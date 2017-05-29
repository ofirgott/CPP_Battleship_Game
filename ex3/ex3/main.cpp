#include "BattleshipTournamentManager.h"
#include <exception>

int main(int argc, char* argv[])
{
	try
	{
		//TODO: create here the logger if we want
		BattleshipTournamentManager Tournament(argc, argv);
		if (Tournament.isTournamentSuccessfullyCreated()) {
			Tournament.Start();
		}
		else {
			//TODO: print to the logger
			return -1;
		}
	}
	catch (std::exception ex)
	{
		//TODO: print to the logger
		return -1;
	}

	return 0;
}
