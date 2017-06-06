#include "BattleshipPrint.h"
#include <iostream>
#include <iomanip>


//todo: move the arg to const, and move the sort function to somewhere ekse
void BattleshipPrint::printStandingsTable(std::vector<StandingsTableEntryData>& sortedPlayersStandings)
{
	std::sort(std::begin(sortedPlayersStandings), std::end(sortedPlayersStandings),
		[](const StandingsTableEntryData& lhs, const StandingsTableEntryData& rhs) {
		return lhs.WinsNumber() > rhs.WinsNumber();
	});

	int placeNum = 1;
	auto nameWidth = max(StandingsTableEntryData::getMaxPlayerNameWidth(sortedPlayersStandings) + 4, strlen("Team Name") + 4);
	int round = 7; //todo: delete
				   /* Table headers */
	setColor(BLUE_COLOR);
	std::cout << "Round " << round << std::endl;
	std::cout << "********" << std::endl << std::endl;
	setColor(WHITE_COLOR);

	std::cout << std::setw(playerNumWidth) << std::left << "#";
	std::cout << std::setw(nameWidth) << std::left << "Team Name";
	std::cout << std::setw(gamesCntWidth) << std::left << "Wins";
	std::cout << std::setw(gamesCntWidth) << std::left << "Losses";
	std::cout << std::setw(precWidth) << std::left << "%";
	std::cout << std::setw(pointsWidth) << std::left << "Pts For";
	std::cout << std::setw(pointsWidth) << std::left << "Pts Against" << std::endl << std::endl;


	for (auto& playerData : sortedPlayersStandings)
	{
		std::cout << std::setw(playerNumWidth) << std::left << std::to_string(placeNum).append(".");
		std::cout << std::setw(nameWidth) << std::left << playerData.PlayerName();
		std::cout << std::setw(gamesCntWidth) << std::left << playerData.WinsNumber();
		std::cout << std::setw(gamesCntWidth) << std::left << playerData.LossesNumber();
		double currPlayerWinsPrec = (static_cast<double>(playerData.WinsNumber()) / (playerData.WinsNumber() + playerData.LossesNumber()) * 100);
		std::cout << std::setw(precWidth) << std::left << std::setprecision(4) << currPlayerWinsPrec;
		std::cout << std::setw(pointsWidth) << std::left << playerData.PointsFor();
		std::cout << std::setw(pointsWidth) << std::left << playerData.PointsAgainst() << std::endl;
		placeNum++;
	}

	std::cout << std::endl << std::endl;

}

void BattleshipPrint::setColor(WORD color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
