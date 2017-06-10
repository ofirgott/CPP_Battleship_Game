#pragma once
#include "IBattleshipGameAlgo.h"
#include "BattleshipBoard.h"


class SingleGameProperties
{
public:
	SingleGameProperties() = delete;
	SingleGameProperties(int boardIndex, int pAIndex, int pBIndex) : mainBoardIndex(boardIndex), playerAIndex(pAIndex), playerBIndex(pBIndex){}

	
	int getPlayerIndexA()const { return playerAIndex; }
	int getPlayerIndexB()const { return playerBIndex; }
	int getBoardIndex()const { return mainBoardIndex; }
	
private:
	int mainBoardIndex;
	int playerAIndex;
	int playerBIndex;
	

};
