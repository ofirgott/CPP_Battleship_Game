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
			system("pause");
			return -1;
		}
	}
	catch (std::exception ex)
	{
		system("pause");
		return -1;
	}

	system("pause");
	return 0;
}
