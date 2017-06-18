#include "BattleshipTournamentManager.h"

int main(int argc, char* argv[])
{
	try
	{
		BattleshipTournamentManager Tournament(argc, argv);
		if (Tournament.isTournamentSuccessfullyCreated()) {
			Tournament.RunTournament();
		}
		else {
			return -1;
		}
	}
	catch (std::exception ex)
	{
		return -1;
	}

	system("pause"); //todo:delete
	return 0;
}
