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
	GetAlgoFuncType getAlgoFunc = nullptr;	/* pointer to the getAlgo function pointer */
	int algosIndexInVec;
	
	PlayerAlgoDetails() = default;
	PlayerAlgoDetails(const PlayerAlgoDetails& other) = delete;
	PlayerAlgoDetails(PlayerAlgoDetails&& otherPlayer) noexcept : dllFileHandle(otherPlayer.dllFileHandle), dllPath(otherPlayer.dllPath), playerName(otherPlayer.playerName), algosIndexInVec(otherPlayer.algosIndexInVec) { std::swap(getAlgoFunc, otherPlayer.getAlgoFunc); }		/* move constructor */
	inline bool operator==(const PlayerAlgoDetails& other) const {
		return algosIndexInVec == other.algosIndexInVec;
	}

};


