#pragma once

#include "BattleshipBoard.h"
#include <windows.h>
#include "PlayerGameResultData.h"

class BattleshipPrint
{
public:

	static const int RED_COLOR = 12;
	static const int BLUE_COLOR = 9;
	static const int YELLOW_COLOR = 14;
	static const int WHITE_COLOR = 15;
	static const char BLANK_CHAR = ' ';
	static const int printDefaultDealy = 400;
	static const bool deafultOneTable = false;
	static const int FIRST_SCREEN_DELAY = 1200;
	

	const static int pointsWidth = 10;
	const static int precWidth = 8;
	const static int gamesCntWidth = 8;
	const static int playerNumWidth = 8;

	static void setDelay(int newDelay) { delay = newDelay; }
	static int getDelay() { return delay; }
	static void setPrintOneTable(bool newMethod) { printOneTable = newMethod; }
	static int getPrintOneTable() { return printOneTable; }
	static void printStandingsTable(std::vector<PlayerGameResultData> sortedPlayersStandings, int currRound, size_t roundsNum);
	
private:
	BattleshipPrint() = delete;
	static void setColor(WORD color);
	static void clearScreen() { system("cls"); }
	
	static int delay;
	static bool printOneTable;
};

