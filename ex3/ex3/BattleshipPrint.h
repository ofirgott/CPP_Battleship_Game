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
	const static int printDefaultDealy = 300;
	

	const static int pointsWidth = 10;
	const static int precWidth = 8;
	const static int gamesCntWidth = 8;
	const static int playerNumWidth = 8;

	static void setDelay(int newDelay) { delay = newDelay; }
	static int getDelay() { return delay; }

	static void printStandingsTable(std::vector<PlayerGameResultData> sortedPlayersStandings, int currRound, size_t roundsNum);
	
private:
	BattleshipPrint() = delete;
	static void hideCursor(); //todo: maybe we cant delete it
	static void showCursor(); //todo: maybe we cant delete it
	static void setColor(WORD color);

	static int delay;

	

};

