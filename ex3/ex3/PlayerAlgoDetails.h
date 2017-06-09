#pragma once

#include <windows.h>
#include <string>
#include "IBattleshipGameAlgo.h"

typedef IBattleshipGameAlgo *(*GetAlgoFuncType)();

struct PlayerAlgoDetails
{
	HINSTANCE dllFileHandle;
	std::string dllPath;
	std::string playerName;			/* short file name, without extentsion (for table) */
	GetAlgoFuncType getAlgoFunc;	/* pointer to the getAlgo function pointer */
	int algosIndexInVec;
	/*todo : create comparator == / != */
};
