#include "BattleshipTournamentManager.h"
#include <exception>
#include "StandingsTableEntryData.h" //todo: delete this
#include "BattleshipPrint.h" //todo: delete this

int main(int argc, char* argv[])
{
	//try
	//{
	//	//TODO: create here the logger if we want
	//	BattleshipTournamentManager Tournament(argc, argv);
	//	if (Tournament.isTournamentSuccessfullyCreated()) {
	//		Tournament.Start();
	//	}
	//	else {
	//		//TODO: print to the logger
	//		return -1;
	//	}
	//}
	//catch (std::exception ex)
	//{
	//	//TODO: print to the logger
	//	return -1;
	//}

	std::vector<StandingsTableEntryData> standings;
	StandingsTableEntryData a("Ofir", 5, 4, 15648, 54664), b("Moshe", 5, 5, 154, 787), c("Sharon", 12, 0, 45454, 48), d("nananananananananananana", 0, 56, 484, 4646), e("Tom", 4, 4, 45, 4544);
	standings.push_back(a);
	standings.push_back(b);
	standings.push_back(c);
	standings.push_back(d);
	standings.push_back(e);
	BattleshipPrint::printStandingsTable(standings);
	system("pause");
	return 0;
}
