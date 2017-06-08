#pragma once
#include "IBattleshipGameAlgo.h"
#include "BattleshipBoard.h"

struct SingleGameProperties
{
	IBattleshipGameAlgo* playerA;
	IBattleshipGameAlgo* playerB;
	BattleshipBoard mainBoard;
};
