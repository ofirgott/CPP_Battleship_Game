#pragma once

/* will be element of the tournament games queue*/

class SingleGameProperties
{
public:
	SingleGameProperties() = delete;
	SingleGameProperties(int boardIndex, int pAIndex, int pBIndex) : mainBoardIndex(boardIndex), playerAIndex(pAIndex), playerBIndex(pBIndex){}

	
	int getPlayerIndexA()const { return playerAIndex; }
	int getPlayerIndexB()const { return playerBIndex; }
	int getBoardIndex()const { return mainBoardIndex; }

	
private:
	int mainBoardIndex;		/* board index in the tournament board vector */
	int playerAIndex;		/* playerA index in the tournament algos vector */
	int playerBIndex;		/* playerB index in the tournament algos vector */
	

};