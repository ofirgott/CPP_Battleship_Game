#pragma once
#include "IBattleshipGameAlgo.h"
#include "BattleshipBoard.h"


class SingleGameProperties
{
public:
	SingleGameProperties() = delete;
	SingleGameProperties(int boardIndex, int pAIndex, int pBIndex) : mainBoardIndex(boardIndex), playerAIndex(pAIndex), playerBIndex(pBIndex){}

	
	int getPlayerAIndex()const { return playerAIndex; }
	int getPlayerBIndex()const { return playerBIndex; }
	int getBoardIndex()const { return mainBoardIndex; }
	
private:
	int mainBoardIndex;
	int playerAIndex;
	int playerBIndex
	

};
