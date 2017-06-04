#pragma once

#include "BattleshipBoard.h"
#include <windows.h>
#include "IBattleshipGameAlgo.h"
#include "StandingsTableEntryData.h"
#include <iostream>
#include <iomanip>


class BattleshipPrint
{
public:

	static const int RED_COLOR = 12;
	static const int BLUE_COLOR = 9;
	static const int YELLOW_COLOR = 14;
	static const int WHITE_COLOR = 15;
	static const int PLAYER_A_COLOR = BLUE_COLOR;
	static const int PLAYER_B_COLOR = YELLOW_COLOR;
	static const int ATTACK_COLOR = RED_COLOR;
	static const char ATTACK_CHAR = '@';
	static const char HIT_CHAR = 'X';
	static const char BLANK_CHAR = ' ';

	const static int printDefatultDealy = 300;
	const static bool printDeafultIsQuiet = false;

	static void printStartBoard(const BattleshipBoard& board);
	static void printCurrentAttack(int playerAttackedId, std::pair<int, int> coord, char currChar, AttackResult res);

	static void setDelay(int newDelay) { delay = newDelay; }
	static void setIsQuiet(bool newIsQuiet) { isQuiet = newIsQuiet; }
	static bool IsQuiet() { return isQuiet; }
	static int getDelay() { return delay; }
	static void setCursorAfterBoard(int rows) { if (!isQuiet) { gotoxy(0, rows + 5); showCursor(); } }


	/* new functions */
	static void printStandingsTable(std::vector<StandingsTableEntryData> sortedPlayersStandings);
	//todo: we need for this function: wins, loses, ptsFor, ptsAgainst. and also we need that vector to be sorted	
private:
	BattleshipPrint() = delete;
	static bool isQuiet;
	static int delay;

	static void gotoxy(const int x, const int y);
	static void hideCursor();
	static void showCursor();
	static void setColor(WORD color);

};

void BattleshipPrint::printStandingsTable(std::vector<StandingsTableEntryData> sortedPlayersStandings)
{
	int placeNum = 1;
	double currPlayerWinsPrec;
	/* Table headers */
	std::cout << "#\tTeam Name\t\tWins\tLosses\t%\tPts For\tPts Against\n\n";

	for(auto playerData: sortedPlayersStandings)
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
