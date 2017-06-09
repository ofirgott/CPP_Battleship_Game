#pragma once
#include "IBattleshipGameAlgo.h"
#include "BattleshipBoard.h"

struct SingleGameProperties
{
	PlayerAlgoDetails* playerA = nullptr;
	PlayerAlgoDetails* playerB = nullptr;
	BattleshipBoard mainBoard;
};
