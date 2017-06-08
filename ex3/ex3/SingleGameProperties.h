#pragma once
#include "IBattleshipGameAlgo.h"
#include "BattleshipBoard.h"

struct SingleGameProperties
{
	IBattleshipGameAlgo* playerA = nullptr;
	IBattleshipGameAlgo* playerB = nullptr;
	BattleshipBoard mainBoard;
};
