#pragma once

#include "BattleshipBoard.h"
#include <windows.h>


class PrintGameBoard
{
public:

	static void printStartBoard(const BattleshipBoard& board);
	static void printCurrentAttack();





private:
	PrintGameBoard(){}
	static bool isQuiet;
	static int delay;

	static void gotoxy(int x, int y);
	static void hideCursor();
	static void setTextColor(WORD color);


};