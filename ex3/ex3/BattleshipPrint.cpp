#include "BattleshipPrint.h"
#include <iostream>
#include <iomanip>

int BattleshipPrint::delay = printDefaultDealy;
bool BattleshipPrint::printOneTable = deafultOneTable;

//get the vector by value because we need a copy of the vector in order to sort it
void BattleshipPrint::printStandingsTable(std::vector<PlayerGameResultData> playersStandingsVec, int currRound, size_t roundsNum)
{
	if (playersStandingsVec.empty() || currRound <= 0 || roundsNum <= 0) return;

	if(printOneTable)
	{
		currRound == 1 ? Sleep(FIRST_SCREEN_DELAY) : Sleep(delay);
		clearScreen();
	}

	std::sort(std::begin(playersStandingsVec), std::end(playersStandingsVec),
		[currRound](const PlayerGameResultData& lhs, const PlayerGameResultData& rhs) {
		double prec_lhs = static_cast<double>(lhs.WinsNumber()) / currRound * 100.0;
		double prec_rhs = static_cast<double>(rhs.WinsNumber()) / currRound * 100.0;
		if (prec_lhs == prec_rhs) return lhs.PointsFor() > rhs.PointsFor();
		else return prec_lhs > prec_rhs;
	});

	int placeNum = 1;

	auto nameWidth = max(PlayerGameResultData::getMaxPlayerNameWidth(playersStandingsVec) + 4, strlen("Team Name") + 4);
	
	/* Table headers */
	setColor(BLUE_COLOR);
	std::cout << "Round " << currRound << "/" << roundsNum << std::endl;
	std::cout << "***********" << std::endl << std::endl;
	setColor(WHITE_COLOR);

	std::cout << std::setw(playerNumWidth) << std::left << "#";
	std::cout << std::setw(nameWidth) << std::left << "Team Name";
	std::cout << std::setw(gamesCntWidth) << std::left << "Wins";
	std::cout << std::setw(gamesCntWidth) << std::left << "Losses";
	std::cout << std::setw(precWidth) << std::left << "%";
	std::cout << std::setw(pointsWidth) << std::left << "Pts For";
	std::cout << std::setw(pointsWidth) << std::left << "Pts Against" << std::endl << std::endl;


	for (auto& playerData : playersStandingsVec)
	{
		std::cout << std::setw(playerNumWidth) << std::left << std::to_string(placeNum).append(".");
		std::cout << std::setw(nameWidth) << std::left << playerData.PlayerName();
		std::cout << std::setw(gamesCntWidth) << std::left << playerData.WinsNumber();
		std::cout << std::setw(gamesCntWidth) << std::left << playerData.LossesNumber();
		double currPlayerWinsPrec = static_cast<double>(playerData.WinsNumber()) / currRound * 100.0;
		std::cout << std::setw(precWidth) << std::left << std::setprecision(4) << currPlayerWinsPrec;
		std::cout << std::setw(pointsWidth) << std::left << playerData.PointsFor();
		std::cout << std::setw(pointsWidth) << std::left << playerData.PointsAgainst() << std::endl;
		placeNum++;
	}

	std::cout << std::endl << std::endl;


	if(currRound == roundsNum)			/* last round, we will print the winner */
	{
		setColor(RED_COLOR);
		std::cout << "*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+" << std::endl;
		std::cout << "The winner is: " << playersStandingsVec[0].PlayerName() << " !" << std::endl;
		std::cout << "*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+" << std::endl;
	}
	setColor(WHITE_COLOR);
}

void BattleshipPrint::setColor(WORD color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
