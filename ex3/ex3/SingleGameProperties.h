#pragma once
#include "IBattleshipGameAlgo.h"
#include "BattleshipBoard.h"


class SingleGameProperties
{
public:
	SingleGameProperties() = delete;
	SingleGameProperties(const BattleshipBoard& board, PlayerAlgoDetails* pA, PlayerAlgoDetails* pB) : mainBoard(board), playerA(pA), playerB(pB){}

	
	PlayerAlgoDetails* getPlayerA()const { return playerA; }
	PlayerAlgoDetails* getPlayerB()const { return playerB; }
	const BattleshipBoard& getBoard()const { return mainBoard; }


private:
	const BattleshipBoard& mainBoard;
	PlayerAlgoDetails* playerA;
	PlayerAlgoDetails* playerB;
	

};
