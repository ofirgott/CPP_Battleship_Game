#include "BattleshipPrint.h"
#include <iostream>
#include <iomanip>

void BattleshipPrint::printStandingsTable(const std::vector<StandingsTableEntryData>& sortedPlayersStandings)
{
	int placeNum = 1;
	size_t maxNameWidth = StandingsTableEntryData::getMaxPlayerNameWidth(sortedPlayersStandings) + 4;
	
	/* Table headers */
	std::cout << "#" << std::setw(maxNameWidth) << "Team Name\t\tWins\tLosses\t%\tPts For\tPts Against\n\n";

	for (auto& playerData : sortedPlayersStandings)
	{
		std::cout << placeNum << ".";
		std::cout << std::setw(maxNameWidth) << playerData.PlayerName() << "\t\t";
		std::cout << playerData.WinsNumber() << "\t";
		std::cout << playerData.LossesNumber() << "\t";
		double currPlayerWinsPrec = (static_cast<double>(playerData.WinsNumber()) / (playerData.WinsNumber() + playerData.LossesNumber()) * 100);
		std::cout << std::setprecision(4) << currPlayerWinsPrec << "\t";
		std::cout << playerData.PointsFor() << "\t";
		std::cout << playerData.PointsAgainst() << "\t" << std::endl;
		placeNum++;
	}

	std::cout << std::endl;

}
