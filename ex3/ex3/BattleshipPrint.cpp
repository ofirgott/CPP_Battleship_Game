#include "BattleshipPrint.h"
#include <iostream>
#include <iomanip>

void BattleshipPrint::printStandingsTable(std::vector<StandingsTableEntryData> sortedPlayersStandings)
{
	int placeNum = 1;
	double currPlayerWinsPrec;
	/* Table headers */
	std::cout << "#\tTeam Name\t\tWins\tLosses\t%\tPts For\tPts Against\n\n";

	for (auto playerData : sortedPlayersStandings)
	{
		std::cout << placeNum << ".\t";
		std::cout << playerData.playerName << "\t\t";
		std::cout << playerData.winsCnt << "\t";
		std::cout << playerData.lossesCnt << "\t";
		currPlayerWinsPrec = (static_cast<double>(playerData.winsCnt) / (playerData.winsCnt + playerData.lossesCnt) * 100);
		std::cout << std::setprecision(4) << currPlayerWinsPrec << "\t";
		std::cout << playerData.pointsForCnt << "\t";
		std::cout << playerData.pointsAgainstCnt << "\t" << std::endl;
		placeNum++;
	}

	std::cout << std::endl;

}
