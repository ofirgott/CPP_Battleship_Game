#include "BattleshipTournamentManager.h"
#include <exception>
#include "StandingsTableEntryData.h" //todo: delete this
#include "BattleshipPrint.h" //todo: delete this
#include <iostream>

int main(int argc, char* argv[])
{
	try
	{
		//TODO: create here the logger if we want
		BattleshipTournamentManager Tournament(argc, argv);
		if (Tournament.isTournamentSuccessfullyCreated()) {
			Tournament.RunTournament();
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

	/*std::vector<StandingsTableEntryData> standings;
	StandingsTableEntryData a("Ofirjldjldjgldjglkdjgkldjkgldngldjogkdl", 5, 4, 15648, 54664), b("Moshe", 6, 3, 154, 787), c("Sharon", 9, 0, 45454, 48), d("dana", 1, 8, 484, 4646), e("Tom", 5, 4, 45, 4544);
	standings.push_back(a);
	standings.push_back(b);
	standings.push_back(c);
	standings.push_back(d);
	standings.push_back(e);
	BattleshipPrint::printStandingsTable(standings);*/

	
	system("pause");
	return 0;
}
